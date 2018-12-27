#ifndef BM168S_GDMA_REG_H
#define BM168S_GDMA_REG_H

/*
 * This file is generated by tools. Do not edit it manually.
 */

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef unsigned long long ullong;

typedef struct {
  u32 pio_gdma_enable;
  u32 des_type;
  u32 chain_end;
  u32 intr_en;
  u32 barrier_enable;
  u32 stride_enable;
  u32 direction;
  u32 acc_write_enable;
  u32 common_mode;
  u32 prefetch_disable;
  u32 hold_des_value;
  u32 Reserved0;
  u32 cmd_id;
  u32 special_func;
  u32 dst_data_format;
  u32 chw_copy;
  u32 sys_mem_type;
  u32 src_data_format;
  u32 lrn_shift_num;
  u32 lrn_shift_dir;
  u32 eng0_sync_id;
  u32 eng1_sync_id;
  u32 eng3_sync_id;
  u32 constant_value;
  u32 src_nstride;
  u32 src_cstride;
  u32 src_hstride;
  u32 src_wstride;
  u32 dst_nstride;
  u32 dst_cstride;
  u32 dst_hstride;
  u32 dst_wstride;
  u32 src_nsize;
  u32 src_csize;
  u32 src_hsize;
  u32 src_wsize;
  u32 dst_nsize;
  u32 dst_csize;
  u32 dst_hsize;
  u32 dst_wsize;
  u32 src_start_addr_l32;
  u32 dst_start_addr_l32;
  u32 src_start_addr_h8;
  u32 dst_start_addr_h8;
  u32 Reserved1;
  u32 src_hshift;
  u32 src_wshift;
  u32 dst_hshift;
  u32 dst_wshift;
  u32 localmem_mask_l32;
  u32 localmem_mask_h32;
  u32 single_step;
  u32 debug_mode;
  u32 Reserved2;
} gdma_reg_t;

static inline void parse_gdma_reg(gdma_reg_t *r, const u32 *p)
{
  r->pio_gdma_enable = p[0] & 1;
  r->des_type = (p[0] >> 1) & 1;
  r->chain_end = (p[0] >> 2) & 1;
  r->intr_en = (p[0] >> 3) & 1;
  r->barrier_enable = (p[0] >> 4) & 1;
  r->stride_enable = (p[0] >> 5) & 1;
  r->direction = (p[0] >> 6) & ((1u << 2) - 1);
  r->acc_write_enable = (p[0] >> 8) & 1;
  r->common_mode = (p[0] >> 9) & 1;
  r->prefetch_disable = (p[0] >> 10) & 1;
  r->hold_des_value = (p[0] >> 11) & 1;
  r->Reserved0 = (p[0] >> 12) & ((1u << 4) - 1);
  r->cmd_id = (p[0] >> 16) & ((1u << 16) - 1);
  r->special_func = p[1] & ((1u << 3) - 1);
  r->dst_data_format = (p[1] >> 3) & ((1u << 3) - 1);
  r->chw_copy = (p[1] >> 6) & 1;
  r->sys_mem_type = (p[1] >> 7) & 1;
  r->src_data_format = (p[1] >> 8) & ((1u << 3) - 1);
  r->lrn_shift_num = (p[1] >> 11) & ((1u << 4) - 1);
  r->lrn_shift_dir = (p[1] >> 15) & 1;
  r->eng0_sync_id = (p[1] >> 16) & ((1u << 16) - 1);
  r->eng1_sync_id = p[2] & ((1u << 16) - 1);
  r->eng3_sync_id = (p[2] >> 16) & ((1u << 16) - 1);
  r->constant_value = p[3];
  r->src_nstride = p[4];
  r->src_cstride = p[5];
  r->src_hstride = p[6];
  r->src_wstride = p[7];
  r->dst_nstride = p[8];
  r->dst_cstride = p[9];
  r->dst_hstride = p[10];
  r->dst_wstride = p[11];
  r->src_nsize = p[12] & ((1u << 16) - 1);
  r->src_csize = (p[12] >> 16) & ((1u << 16) - 1);
  r->src_hsize = p[13] & ((1u << 16) - 1);
  r->src_wsize = (p[13] >> 16) & ((1u << 16) - 1);
  r->dst_nsize = p[14] & ((1u << 16) - 1);
  r->dst_csize = (p[14] >> 16) & ((1u << 16) - 1);
  r->dst_hsize = p[15] & ((1u << 16) - 1);
  r->dst_wsize = (p[15] >> 16) & ((1u << 16) - 1);
  r->src_start_addr_l32 = p[16];
  r->dst_start_addr_l32 = p[17];
  r->src_start_addr_h8 = p[18] & ((1u << 8) - 1);
  r->dst_start_addr_h8 = (p[18] >> 8) & ((1u << 8) - 1);
  r->Reserved1 = (p[18] >> 16) & ((1u << 16) - 1);
  r->src_hshift = p[19] & ((1u << 8) - 1);
  r->src_wshift = (p[19] >> 8) & ((1u << 8) - 1);
  r->dst_hshift = (p[19] >> 16) & ((1u << 8) - 1);
  r->dst_wshift = (p[19] >> 24) & ((1u << 8) - 1);
  r->localmem_mask_l32 = p[20];
  r->localmem_mask_h32 = p[21];
  r->single_step = p[26] & 1;
  r->debug_mode = (p[26] >> 1) & 1;
  r->Reserved2 = (p[26] >> 2) & ((1u << 30) - 1);
}

static inline void emit_gdma_reg(const gdma_reg_t *r, u32 *_p)
{
  volatile u32 *p = (typeof(p))_p;
  p[26] = (r->single_step & 1) |
          ((r->debug_mode & 1) << 1) |
          ((r->Reserved2 & ((1u << 30) - 1)) << 2);
  p[21] = (r->localmem_mask_h32 & (((u64)1 << 32) - 1));
  p[20] = (r->localmem_mask_l32 & (((u64)1 << 32) - 1));
  p[19] = (r->src_hshift & ((1u << 8) - 1)) |
          ((r->src_wshift & ((1u << 8) - 1)) << 8) |
          ((r->dst_hshift & ((1u << 8) - 1)) << 16) |
          ((r->dst_wshift & ((1u << 8) - 1)) << 24);
  p[18] = (r->src_start_addr_h8 & ((1u << 8) - 1)) |
          ((r->dst_start_addr_h8 & ((1u << 8) - 1)) << 8) |
          ((r->Reserved1 & ((1u << 16) - 1)) << 16);
  p[17] = (r->dst_start_addr_l32 & (((u64)1 << 32) - 1));
  p[16] = (r->src_start_addr_l32 & (((u64)1 << 32) - 1));
  p[15] = (r->dst_hsize & ((1u << 16) - 1)) |
          ((r->dst_wsize & ((1u << 16) - 1)) << 16);
  p[14] = (r->dst_nsize & ((1u << 16) - 1)) |
          ((r->dst_csize & ((1u << 16) - 1)) << 16);
  p[13] = (r->src_hsize & ((1u << 16) - 1)) |
          ((r->src_wsize & ((1u << 16) - 1)) << 16);
  p[12] = (r->src_nsize & ((1u << 16) - 1)) |
          ((r->src_csize & ((1u << 16) - 1)) << 16);
  p[11] = (r->dst_wstride & (((u64)1 << 32) - 1));
  p[10] = (r->dst_hstride & (((u64)1 << 32) - 1));
  p[9] = (r->dst_cstride & (((u64)1 << 32) - 1));
  p[8] = (r->dst_nstride & (((u64)1 << 32) - 1));
  p[7] = (r->src_wstride & (((u64)1 << 32) - 1));
  p[6] = (r->src_hstride & (((u64)1 << 32) - 1));
  p[5] = (r->src_cstride & (((u64)1 << 32) - 1));
  p[4] = (r->src_nstride & (((u64)1 << 32) - 1));
  p[3] = (r->constant_value & (((u64)1 << 32) - 1));
  p[2] = (r->eng1_sync_id & ((1u << 16) - 1)) |
         ((r->eng3_sync_id & ((1u << 16) - 1)) << 16);
  p[1] = (r->special_func & ((1u << 3) - 1)) |
         ((r->dst_data_format & ((1u << 3) - 1)) << 3) |
         ((r->chw_copy & 1) << 6) |
         ((r->sys_mem_type & 1) << 7) |
         ((r->src_data_format & ((1u << 3) - 1)) << 8) |
         ((r->lrn_shift_num & ((1u << 4) - 1)) << 11) |
         ((r->lrn_shift_dir & 1) << 15) |
         ((r->eng0_sync_id & ((1u << 16) - 1)) << 16);
  p[0] = (r->pio_gdma_enable & 1) |
         ((r->des_type & 1) << 1) |
         ((r->chain_end & 1) << 2) |
         ((r->intr_en & 1) << 3) |
         ((r->barrier_enable & 1) << 4) |
         ((r->stride_enable & 1) << 5) |
         ((r->direction & ((1u << 2) - 1)) << 6) |
         ((r->acc_write_enable & 1) << 8) |
         ((r->common_mode & 1) << 9) |
         ((r->prefetch_disable & 1) << 10) |
         ((r->hold_des_value & 1) << 11) |
         ((r->Reserved0 & ((1u << 4) - 1)) << 12) |
         ((r->cmd_id & ((1u << 16) - 1)) << 16);
}

static inline void reset_gdma_reg(gdma_reg_t *r)
{
  r->pio_gdma_enable = 0b0;
  r->des_type = 0b0;
  r->chain_end = 0b0;
  r->intr_en = 0b0;
  r->barrier_enable = 0b0;
  r->stride_enable = 0b0;
  r->direction = 0b00;
  r->acc_write_enable = 0b0;
  r->common_mode = 0b0;
  r->prefetch_disable = 1;
  r->hold_des_value = 0b0;
  r->Reserved0 = 0b0;
  r->cmd_id = 0b0;
  r->special_func = 0;
  r->dst_data_format = 0;
  r->chw_copy = 1;
  r->sys_mem_type = 0;
  r->src_data_format = 0;
  r->lrn_shift_num = 1;
  r->lrn_shift_dir = 0;
  r->eng0_sync_id = 0b0;
  r->eng1_sync_id = 0b0;
  r->eng3_sync_id = 0b0;
  r->constant_value = 0b0;
  r->src_nstride = 0;
  r->src_cstride = 0;
  r->src_hstride = 0;
  r->src_wstride = 1;
  r->dst_nstride = 0;
  r->dst_cstride = 0;
  r->dst_hstride = 0;
  r->dst_wstride = 1;
  r->src_nsize = 0x0;
  r->src_csize = 0x0;
  r->src_hsize = 0x0;
  r->src_wsize = 0x0;
  r->dst_nsize = 0x0;
  r->dst_csize = 0x0;
  r->dst_hsize = 0x0;
  r->dst_wsize = 0x0;
  r->src_start_addr_l32 = 0b0;
  r->dst_start_addr_l32 = 0b0;
  r->src_start_addr_h8 = 0b0;
  r->dst_start_addr_h8 = 0;
  r->Reserved1 = 0b0;
  r->src_hshift = 0;
  r->src_wshift = 0;
  r->dst_hshift = 0;
  r->dst_wshift = 0;
  r->localmem_mask_l32 = 0xffffffff;
  r->localmem_mask_h32 = 0xffffffff;
  r->single_step = 0;
  r->debug_mode = 0;
  r->Reserved2 = 0b0;
}

static inline void trace_gdma_reg(gdma_reg_t *r, const char *tag)
{
#define trace_one_reg(name) \
  printf("  %s: %llx\n", #name, (ullong)r->name)

  printf("--- %s ---\n", tag);
  trace_one_reg(pio_gdma_enable);
  trace_one_reg(des_type);
  trace_one_reg(chain_end);
  trace_one_reg(intr_en);
  trace_one_reg(barrier_enable);
  trace_one_reg(stride_enable);
  trace_one_reg(direction);
  trace_one_reg(acc_write_enable);
  trace_one_reg(common_mode);
  trace_one_reg(prefetch_disable);
  trace_one_reg(hold_des_value);
  trace_one_reg(Reserved0);
  trace_one_reg(cmd_id);
  trace_one_reg(special_func);
  trace_one_reg(dst_data_format);
  trace_one_reg(chw_copy);
  trace_one_reg(sys_mem_type);
  trace_one_reg(src_data_format);
  trace_one_reg(lrn_shift_num);
  trace_one_reg(lrn_shift_dir);
  trace_one_reg(eng0_sync_id);
  trace_one_reg(eng1_sync_id);
  trace_one_reg(eng3_sync_id);
  trace_one_reg(constant_value);
  trace_one_reg(src_nstride);
  trace_one_reg(src_cstride);
  trace_one_reg(src_hstride);
  trace_one_reg(src_wstride);
  trace_one_reg(dst_nstride);
  trace_one_reg(dst_cstride);
  trace_one_reg(dst_hstride);
  trace_one_reg(dst_wstride);
  trace_one_reg(src_nsize);
  trace_one_reg(src_csize);
  trace_one_reg(src_hsize);
  trace_one_reg(src_wsize);
  trace_one_reg(dst_nsize);
  trace_one_reg(dst_csize);
  trace_one_reg(dst_hsize);
  trace_one_reg(dst_wsize);
  trace_one_reg(src_start_addr_l32);
  trace_one_reg(dst_start_addr_l32);
  trace_one_reg(src_start_addr_h8);
  trace_one_reg(dst_start_addr_h8);
  trace_one_reg(Reserved1);
  trace_one_reg(src_hshift);
  trace_one_reg(src_wshift);
  trace_one_reg(dst_hshift);
  trace_one_reg(dst_wshift);
  trace_one_reg(localmem_mask_l32);
  trace_one_reg(localmem_mask_h32);
  trace_one_reg(single_step);
  trace_one_reg(debug_mode);
  trace_one_reg(Reserved2);
}

#endif
