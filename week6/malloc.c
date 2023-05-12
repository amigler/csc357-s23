// from section 8.7 of the C Programming Language by K & R
#include <stdio.h>
#include <stdlib.h>

typedef long Align; /* used for alignment on long boundary */

union header {		/* block header: */
	struct {
		union header *ptr;	/* next block if on free list */
		unsigned int size;		/* size of this block */
	} s;
	Align x;		/* force alignment of blocks */
};

typedef union header Header;

Header *morecore(unsigned int);
void *custom_malloc(unsigned int nbytes);
void free(void *ap);

static Header base;		/* empty list to get started */
static Header *freep = NULL;	/* start of free list */

void print_free_list() {
    printf("base: %p\n", &base);
    printf("base.s.size: %d\n", base.s.size);
    printf("freep: %p\n", freep);
    printf("freep->s.size: %d\n", freep->s.size);
    
    Header *p, *prevp = freep;
    for (p = prevp->s.ptr; p != freep; prevp = p, p = p->s.ptr) {
        printf("p->s.size = %lu, p->s.ptr = %p\n", p->s.size * sizeof(Header), p->s.ptr);
    }
}

int main(int argc, char *argv[]) {

    char *s = custom_malloc(10000);

    print_free_list();
    
    char *s2 = custom_malloc(1200000);

    print_free_list();
    
    char *s3 = custom_malloc(1200);

    print_free_list();
    
    return EXIT_SUCCESS;
}

/* malloc: general-purpose storage allocator */
void *custom_malloc(unsigned int nbytes)
{
    Header *p, *prevp;
    unsigned int nunits;

    nunits = (nbytes+sizeof(Header)-1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {	/* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {	/* large enough */
            if (p->s.size == nunits) {	/* exactly the right size */
                prevp->s.ptr = p->s.ptr;
            } else {			/* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) {		/* wrapped around free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL;	/* none left */
            }
        }
    }
}

#define NALLOC 1024	/* minimum units to request */

/* morecore: ask system for more memory using sbrk() system call */
Header *morecore(unsigned int nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) - 1) { 	/* no space at all */
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;
        
    bp = (Header *) ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;
        }
    }
    
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

