#ifndef _EXT2_H_
#define _EXT2_H_

#include "ext2_fs.h"
#include "vfs/fs.h"
#include <stdio.h>

struct file_system_type myfs;
struct super_block *sb;

struct file_system_type *initialize_ext2(const char *image_path);

/* read and parse superblock */
struct super_block *get_superblock(struct file_system_type *fs);

/* fill kstatf struct */
int statfs(struct super_block *sb, struct kstatfs *stat);

/* fill inode struct from inode table */
void ext2_read_inode(struct inode *i);

/* search a single block for given file name */
void *search_block(void *addr, const char *n);

struct inode *inode_from_table(unsigned int inode);
void read_inode_to_table(unsigned int inode);
void ext2_read_inode(struct inode *i);
int ext2_read_block(unsigned int block, filldir_t f);
// i_op
struct dentry *ext2_lookup(struct inode *i, struct dentry *d);
int ext2_readlink(struct dentry *d, char *p, int len);
int ext2_readlink_i(struct inode *d, char *p, int len);
int ext2_readdir(struct inode *i, filldir_t f);
int ext2_getattr(struct dentry *d, struct kstat *k);
// f_op
loffset_t ext2_llseek(struct file *f, loffset_t o, int whence);
ssize_t ext2_read(struct file *f, char *buf, size_t len, loffset_t *o);
int ext2_open(struct inode *i, struct file *f);
int ext2_release(struct inode *i, struct file *f);

void *flatten_data(struct inode *i);
void flatten_indirects(void *dest, void *src, unsigned int blocks);
void flatten_d_indirects(void *dest, void *src, unsigned int blocks);
void flatten_t_indirects(void *dest, void *src, unsigned int blocks);
#endif
