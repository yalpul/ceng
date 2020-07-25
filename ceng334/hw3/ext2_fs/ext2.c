#include "ext2.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BASE_OFFSET 1024 /* location of the superblock in the first group */

struct super_operations s_op;
struct inode_operations i_op;
struct file_operations f_op;

void *fs_data;
void *inode_table_addr;
void *blkdscrptrs;
struct super_block *sb;

struct inode *inode_table;

char fs_name[] = "ext2";

/* Implement functions in s_op, i_op, f_op here */

struct file_system_type *initialize_ext2(const char *image_path) {
  // Fill i_op
  i_op.lookup = ext2_lookup;
  i_op.readdir = ext2_readdir;
  i_op.getattr = ext2_getattr;
  i_op.readlink = ext2_readlink;
  // Fill f_op
  f_op.llseek = ext2_llseek;
  f_op.read = ext2_read;
  f_op.open = ext2_open;
  f_op.release = ext2_release;
  myfs.name = fs_name;
  myfs.file_descriptor = open(image_path, O_RDONLY);
  struct stat st;
  fstat(myfs.file_descriptor, &st);
  myfs.get_superblock = get_superblock;
  fs_data = mmap(NULL, st.st_size, PROT_READ,
      MAP_FILE | MAP_PRIVATE, myfs.file_descriptor, 0);
  s_op.read_inode = ext2_read_inode;
  s_op.statfs = statfs;
  get_superblock(&myfs);
  inode_table = malloc(sizeof(struct inode)*sb->s_inodes_count);
  inode_table_addr = fs_data +
    (*(unsigned int*) (fs_data + 1024 + 1024 + 8)) * sb->s_blocksize;
  blkdscrptrs = fs_data + 1024 + sb->s_blocksize;
  return &myfs;
}

int statfs(struct super_block *sb, struct kstatfs *stat)
{
  if (sb == NULL || stat == NULL)
    return 1;
  stat->name = sb->s_type->name;
  stat->f_magic = sb->s_magic;
  stat->f_bsize = sb->s_blocksize;
  stat->f_blocks = sb->s_blocks_count;
  stat->f_bfree = sb->s_free_blocks_count;
  stat->f_inodes = sb->s_inodes_count;
  stat->f_finodes = sb->s_free_inodes_count;
  stat->f_inode_size = sb->s_inode_size;
  stat->f_minor_rev_level = sb->s_minor_rev_level;
  stat->f_rev_level = sb->s_rev_level;
  stat->f_namelen = strlen(stat->name);

  return 0;
}

struct super_block *get_superblock(struct file_system_type *fs)
{
  if (sb)
    return sb;

  sb = malloc(sizeof(struct super_block));
  void *sb_addr = fs_data+BASE_OFFSET;

  sb->s_inodes_count = *(unsigned int*)(sb_addr + 0);
  sb->s_blocks_count = *(unsigned int*)(sb_addr + 4);
  sb->s_free_blocks_count = *(unsigned int*)(sb_addr + 12);
  sb->s_free_inodes_count = *(unsigned int*)(sb_addr + 16);
  sb->s_blocksize = 1 << (*(unsigned long*)(sb_addr + 24)+10);
  sb->s_blocksize_bits = *(unsigned long*)(sb_addr + 24)+10;
  sb->s_blocks_per_group = *(unsigned int*)(sb_addr + 32);
  sb->s_inodes_per_group = *(unsigned int*)(sb_addr + 40);
  sb->s_minor_rev_level = *(unsigned short*)(sb_addr + 62);
  sb->s_rev_level = *(unsigned int*)(sb_addr + 76);
  sb->s_first_ino = (sb->s_rev_level >= 1) ?
    *(unsigned int*)(sb_addr+84) : 11;
  sb->s_inode_size = (sb->s_rev_level >= 1) ?
    *(unsigned short*)(sb_addr+88) : 128;
  sb->s_block_group_nr = *(unsigned short*)(sb_addr+90);
  unsigned int b = sb->s_blocksize/4;
  sb->s_maxbytes = sb->s_blocksize*(b*b*b + b*b + b + 12);
  unsigned int f = *(unsigned int*)(sb_addr + 1024 + 8);
  sb->s_first_data_block =
    f + sb->s_inodes_count * sb->s_inode_size / sb->s_blocksize;
  sb->s_type = &myfs;
  sb->s_op = &s_op;
  sb->s_flags = 0; //todo
  sb->s_magic = 0xef53;
  sb->s_root = NULL; // todo 
  sb->s_fs_info = NULL; // todo
  return sb;
}

void ext2_read_inode(struct inode *i)
{
  unsigned int inode = i->i_ino;
  read_inode_to_table(inode-1);
  *i = inode_table[inode-1];
}

void *get_inode_loc(unsigned int inode)
{
  unsigned int blkgrp = (inode)/sb->s_inodes_per_group;
  void *bdesc = blkdscrptrs + blkgrp*0x20;
  unsigned int block = *(unsigned int*)(bdesc+8);
  void *inode_table = fs_data + block*sb->s_blocksize;
  return inode_table + (inode)%sb->s_inodes_per_group*sb->s_inode_size;
}

void read_inode_to_table(unsigned int inode)
{
  void *node = get_inode_loc(inode);
  struct inode i;
  i.i_ino = inode+1;
  i.i_mode = *(unsigned short*) node;
  i.i_nlink = *(unsigned short*) (node + 26);
  i.i_uid = *(unsigned short*) (node + 2);
  i.i_gid = *(unsigned short*) (node + 24);
  i.i_size = *(unsigned int*) (node + 4);
  i.i_atime = *(unsigned int*) (node + 8);
  i.i_mtime = *(unsigned int*) (node + 16);
  i.i_ctime = *(unsigned int*) (node + 12);
  i.i_op = &i_op;
  i.f_op = &f_op;
  i.i_sb = sb;
  i.i_state = 0L; // TODO what is this?
  i.i_flags = *(unsigned int*) (node + 32);
  for (int j = 0; j < 15; j++)
    i.i_block[j] = *(unsigned int*)(node + 40 + j*4);
  i.i_blocks = (i.i_size+sb->s_blocksize-1) / sb->s_blocksize;
  inode_table[inode] = i;
}

struct inode *inode_from_table(unsigned int inode)
{
  read_inode_to_table(inode-1);
  return &inode_table[inode-1];
}

struct dentry *ext2_lookup(struct inode *i, struct dentry *d)
{
  void *data = flatten_data(i);
  void *current = data;
  while (current < data + i->i_size)
  {
    unsigned int inode = *(unsigned int*)current;
    unsigned short size = *(unsigned short*)(current+4);
    unsigned char len = *(unsigned char*)(current+6);
    const char *name = current + 8;
    if (strncmp(name, d->d_name, strlen(d->d_name)) == 0)
    {
      struct inode *node = inode_from_table(inode);
      d->d_inode = node;
      d->d_sb = sb;
      d->d_parent = NULL; // TODO
      d->d_fsdata = NULL; // TODO
      free(data);
      return d;
    }
    else
      current += size;
  }
  free(data);
  return NULL;
}

void *search_block(void *addr, const char *n)
{
  void *lim = addr + sb->s_blocksize;
  while (addr < lim)
  {
    unsigned int inode = *(unsigned int*)addr;
    unsigned short size = *(unsigned short*)(addr+4);
    unsigned char len = *(unsigned char*)(addr+6);
    const char *name = addr + 8;
    if (strncmp(name, n, len) == 0)
      return addr;
    else
      addr += size;
  }
  return NULL;
}

int ext2_readdir(struct inode *i, filldir_t f)
{
  unsigned int entries = 0;
  void *data = flatten_data(i);
  void *current = data;
  while (current < data + i->i_size)
  {
    char name[256];
    unsigned int ino = *(unsigned int*)current;
    unsigned short entry_len = *(unsigned short*)(current+4);
    unsigned char name_len = *(unsigned char*)(current+6);
    memcpy(name, current+8, name_len);
    name[name_len] = '\0';
    f(name, name_len, ino);
    current += entry_len;
    entries++;
  }

  free(data);
  return entries;
}

int ext2_getattr(struct dentry *d, struct kstat *k)
{
  if (d == NULL || d->d_inode == NULL)
    return 1;
  struct inode *i = d->d_inode;
  k->ino = i->i_ino;
  k->mode = i->i_mode;
  k->nlink = i->i_nlink;
  k->uid = i->i_uid;
  k->gid = i->i_gid;
  k->size = i->i_size;
  k->atime = i->i_atime;
  k->mtime = i->i_mtime;
  k->ctime = i->i_ctime;
  k->blksize = sb->s_blocksize;
  k->blocks = i->i_blocks;
  return 0;
}

int ext2_readlink(struct dentry *d, char *p, int len)
{
  struct inode *i = d->d_inode;
  return ext2_readlink_i(i, p, len);
}

int ext2_readlink_i(struct inode *i, char *p, int len)
{
  if (i->i_size <= 60)
  {
    int namelen = strlen((const char*)&i->i_block[0]);
    if (namelen < len)
      len = namelen;
    memcpy(p, &i->i_block[0], len);
    return len;
  }
  else
  {
    memcpy(p, fs_data+i->i_block[0]*sb->s_blocksize, i->i_size);
    return i->i_size;
  }
}

loffset_t ext2_llseek(struct file *f, loffset_t o, int whence)
{
  unsigned long lim = f->f_inode->i_size;
  if (whence == SEEK_SET)
    f->f_pos = (o < 0 ? 0 : (o > lim ? lim : o));
  else if (whence == SEEK_CUR)
    f->f_pos = ((f->f_pos+o) < 0 ? 0 :
        ((f->f_pos+o) > lim ? lim : (f->f_pos+o)));
  else if (whence == SEEK_END)
    f->f_pos = (lim+o < 0 ? 0 :
        (lim+o > lim ? lim : lim+o));
  else
  {
    fprintf(stderr, "%s\n", "Invalid arg to llseek");
    exit(1);
  }
  return f->f_pos;
}

ssize_t ext2_read(struct file *f, char *buf, size_t len, loffset_t *o)
{
  struct inode *i = f->f_inode;
  void *data = flatten_data(i);
  f->f_pos = *o;
  unsigned long lim = (*o+len <= i->i_size) ? len : i->i_size-*o;
  memcpy(buf, data+*o, lim);
  f->f_pos += lim;
  free(data);
  return lim;
}

void *flatten_data(struct inode *i)
{
  unsigned long blocks = i->i_blocks;
  void *data = malloc(blocks*sb->s_blocksize);
  unsigned int ptr_per_block = sb->s_blocksize/4;
  if (blocks < 12)
    for (int j = 0; j < blocks; j++)
      memcpy(data+j*sb->s_blocksize, fs_data+i->i_block[j]*sb->s_blocksize,
          sb->s_blocksize);
  else if (blocks < 12 + ptr_per_block)
  {
    for (int j = 0; j < 12; j++)
      memcpy(data+j*sb->s_blocksize, fs_data+i->i_block[j]*sb->s_blocksize,
          sb->s_blocksize);
    blocks -= 12;
    flatten_indirects(data+12*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[12], blocks);
  }
  else if (blocks < 12 + ptr_per_block + ptr_per_block*ptr_per_block)
  {
    for (int j = 0; j < 12; j++)
      memcpy(data+j*sb->s_blocksize, fs_data+i->i_block[j]*sb->s_blocksize,
          sb->s_blocksize);
    blocks -= 12;
    flatten_indirects(data+12*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[12], ptr_per_block);
    blocks -= ptr_per_block;
    flatten_d_indirects(data+(12+ptr_per_block)*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[13], blocks);
  }
  else
  {
    for (int j = 0; j < 12; j++)
      memcpy(data+j*sb->s_blocksize, fs_data+i->i_block[j]*sb->s_blocksize,
          sb->s_blocksize);
    blocks -= 12;
    flatten_indirects(data+12*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[12], ptr_per_block);
    blocks -= ptr_per_block;
    flatten_d_indirects(data+(12+ptr_per_block)*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[13], ptr_per_block*ptr_per_block);

    blocks -= ptr_per_block*ptr_per_block;
    flatten_t_indirects(
        data+(12+ptr_per_block+ptr_per_block*ptr_per_block)*sb->s_blocksize,
        fs_data+sb->s_blocksize*i->i_block[14], blocks);
  }
  return data;
}

void flatten_t_indirects(void *dest, void *src, unsigned int blocks)
{
  int i = 0;
  unsigned int ptr_per_block = sb->s_blocksize/4;
  while (blocks > ptr_per_block*ptr_per_block)
  {
    flatten_d_indirects(dest+i*ptr_per_block*ptr_per_block*sb->s_blocksize,
        *(unsigned int*)(src+i*4)*sb->s_blocksize+fs_data,
        ptr_per_block*ptr_per_block);
    blocks -= ptr_per_block*ptr_per_block;
    i++;
  }
  flatten_d_indirects(dest+i*ptr_per_block*ptr_per_block*sb->s_blocksize,
      *(unsigned int*)(src+i*4)*sb->s_blocksize+fs_data, blocks);
}

void flatten_d_indirects(void *dest, void *src, unsigned int blocks)
{
  int i = 0;
  unsigned int ptr_per_block = sb->s_blocksize/4;
  while (blocks > ptr_per_block)
  {
    flatten_indirects(dest+i*ptr_per_block*sb->s_blocksize,
        *(unsigned int*)(src+i*4)*sb->s_blocksize+fs_data, ptr_per_block);
    blocks -= ptr_per_block;
    i++;

  }
  flatten_indirects(dest+i*ptr_per_block*sb->s_blocksize,
      *(unsigned int*)(src+i*4)*sb->s_blocksize+fs_data, blocks);
}

void flatten_indirects(void *dest, void *src, unsigned int blocks)
{
  for (int i = 0; i < blocks; i++)
    memcpy(dest+i*sb->s_blocksize,
        *(unsigned int*)(src+i*4)*sb->s_blocksize+fs_data,
        sb->s_blocksize);
}

int ext2_open(struct inode *i, struct file *f)
{
  if (i == NULL || f == NULL)
    return 1;
  int status;
  if (S_ISLNK(i->i_mode))
  {
    // Follow link
    char path[256];
    ext2_readlink_i(i, path, 256);
    struct dentry *d = pathwalk(path);
    status = ext2_open(d->d_inode, f);
    free(d);
  }
  else
  {
    f->f_inode = i;
    f->f_op = &f_op;
    f->f_flags = i->i_flags;
    f->f_mode = i->i_mode;
    f->f_pos = 0;
    status = 0;
  }
  return status;
}

int ext2_release(struct inode *i, struct file *f)
{
  if (i == NULL || f == NULL)
    return 1;
  return 0;
}
