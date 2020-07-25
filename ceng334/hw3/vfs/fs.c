#include "fs.h"
#include "ext2_fs/ext2.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int init_fs(const char *image_path) {
  current_fs = initialize_ext2(image_path);
  current_sb = current_fs->get_superblock(current_fs);
  return !(current_fs && current_sb);
}

struct file *openfile(char *path) {
  struct file *f = malloc(sizeof(struct file));
  f->f_path = malloc(strlen(path) + 1);
  strcpy(f->f_path, path);
  struct dentry *dir = pathwalk(path);
  if (!dir) {
    return NULL;
  }
  f->f_inode = dir->d_inode;
  free(dir);
  if (f->f_inode->f_op->open(f->f_inode, f)) {
    return NULL;
  }
  return f;
}

int closefile(struct file *f) {
  if (f->f_op->release(f->f_inode, f)) {
    printf("Error closing file\n");
  }
  free(f);
  f = NULL;
  return 0;
}

int readfile(struct file *f, char *buf, int size, loffset_t *offset) {
  if (*offset >= f->f_inode->i_size) {
    return 0;
  }
  if (*offset + size >= f->f_inode->i_size) {
    size = f->f_inode->i_size - *offset;
  }
  // May add llseek call
  return f->f_op->read(f, buf, size, offset);
}

struct dentry *pathwalk(char *path) {
  /* Allocates and returns a new dentry for a given path */
  struct inode root;
  struct dentry *de = malloc(sizeof(struct dentry));
  struct dentry *d_entry;
  struct inode *current = inode_from_table(2);
  root.i_ino = 2;
  ext2_read_inode(&root);
  char filename[255];
  int i;
  int file_i = 0;
  int path_len = strlen(path);
  if (path_len > 1)
  {
    for (i = 1; i < path_len; i++, file_i++)
    {
      if (path[i] == '/')
      {
        i++;
        filename[file_i] = '\0';
        file_i = 0;
        de->d_name = filename;
        d_entry = ext2_lookup(current, de);
        if (d_entry == NULL)
        {
          free(de);
          return NULL;
        }
        current = de->d_inode;
      }
      filename[file_i] = path[i];
    }
    filename[file_i] = '\0';
    de->d_name = filename;
    d_entry = ext2_lookup(current, de);
    if (d_entry == NULL)
    {
      free(de);
      return NULL;
    }
  }
  else
  {
    de->d_name = path+1;
    de->d_sb = sb;
    de->d_fsdata = NULL; // what is this?
    de->d_parent = de;
    de->d_inode = inode_from_table(2);
    de->d_flags = de->d_inode->i_flags;
  }
  return de;
}

int statfile(struct dentry *d_entry, struct kstat *k_stat) {
  return d_entry->d_inode->i_op->getattr(d_entry, k_stat);
}
