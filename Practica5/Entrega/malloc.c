#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


/*------------ ESTRUCTURA DEL BLOC ------------*/
struct m_block {
  size_t size;	//Mida del bloc
  struct m_block *next;	//Adreça del següent bloc
  int free;	//Estat del bloc , reservat o no
};


/*------------ FUNCIÓ PER SABER L'ADREÇA DEL BLOC ------------*/

struct m_block *get_block_ptr(void *ptr) {
  return (struct m_block*)ptr - 1;
}

/*------------ DEFINIM EL TAMANY DE L'ESTRUCTURA DEL BLOC ------------*/
#define META_SIZE sizeof(struct m_block)


/*------------ INICI DE LA LLISTA ENLLAÇADA ------------*/
void *global_base = NULL;


/*------------------- FUNCIÓ PER BUSCAR UN BLOC LLIURE -----------------*/
struct m_block *find_free_block(struct m_block **last, size_t size) {
  struct m_block *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

/*------------------- FUNCIÓ PER RESERVAR ESPAI -----------------*/
struct m_block *request_space(struct m_block* last, size_t size) {
  struct m_block *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request);	
  if (request == (void*) -1) {
    return NULL;
  }

  if (last) { 
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

/*---------------- FUNCIÓ MALLOC -----------------*/
void *malloc(size_t size) {

  struct m_block *block;
  
  if (size <= 0) {
    return NULL;
  }

  if (!global_base) { 
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct m_block *last = global_base;
    block = find_free_block(&last, size);
    if (!block) { 
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      
      
      block->free = 0;
    }
  }

  return(block+1);	//Retornem l'apuntador apuntant a la zona de memòria 
  					//contigua al nostre meta dada.
}



/*---------------- FUNCIÓ FREE -----------------*/
void free(void *ptr) {
  if (!ptr) {	//Controlem que l'apuntador sigui NULL o no
    return;
  }

  struct m_block* block_ptr = get_block_ptr(ptr);
  assert(block_ptr->free == 0);
  block_ptr->free = 1;	//Posem l'atribut free a 1
  
}



/*---------------- FUNCIÓ REALLOC -----------------*/
void *realloc(void *ptr, size_t size) {
  if (!ptr) {	//Controlem que l'apuntador sigui NULL o no
    
    return malloc(size);
  }

  struct m_block* block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    
    return ptr;
  }

  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL; 
  }
  memcpy(new_ptr, ptr, block_ptr->size); //Copiem el contingut d'un bloc a un altre
  free(ptr);
  return new_ptr;
}


/*---------------- FUNCIÓ CALLOC -----------------*/
void *calloc(size_t nelem, size_t elsize) {
  size_t size = nelem * elsize; 
  void *ptr = malloc(size);
  memset(ptr, 0, size);	//Deixem el bloc de memòria a zero
  return ptr;
}