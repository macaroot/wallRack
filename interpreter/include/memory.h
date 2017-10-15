#ifndef MEMORY_H
#define MEMORY_H

/* Memory interface */
void mem_grow_rack(void);
void mem_grow_wall(void);
void mem_grow_raw(void);
void mem_grow_tokens(void);
/*
 *void mem_reduce_rack(void);
 *void mem_reduce_wall(void);
 */
void mem_wipe_raw(void);
void mem_wipe_rest(void);
void mem_init_wall_rack(void);

#endif

