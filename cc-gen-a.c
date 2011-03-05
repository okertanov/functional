/* Generated from cc-gen-a.ss by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2011-03-05 21:42
   Version 4.2.0
   linux-unix-gnu-x86 [ manyargs dload ptables applyhook ]
   compiled 2009-11-30 on vernadsky (Linux)
   command line: cc-gen-a.ss
   used units: library eval data_structures ports extras srfi_69
*/

#include "chicken.h"

static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_data_structures_toplevel)
C_externimport void C_ccall C_data_structures_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_ports_toplevel)
C_externimport void C_ccall C_ports_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_extras_toplevel)
C_externimport void C_ccall C_extras_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_srfi_69_toplevel)
C_externimport void C_ccall C_srfi_69_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[5];
static double C_possibly_force_alignment;
static C_char C_TLS li0[] C_aligned={C_lihdr(0,0,13),40,115,117,109,32,120,48,32,46,32,121,49,41,0,0,0};
static C_char C_TLS li1[] C_aligned={C_lihdr(0,0,10),40,116,111,112,108,101,118,101,108,41,0,0,0,0,0,0};


C_noret_decl(C_toplevel)
C_externexport void C_ccall C_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_17)
static void C_ccall f_17(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_20)
static void C_ccall f_20(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_23)
static void C_ccall f_23(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_26)
static void C_ccall f_26(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_29)
static void C_ccall f_29(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_32)
static void C_ccall f_32(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_54)
static void C_ccall f_54(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_41)
static void C_ccall f_41(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_44)
static void C_ccall f_44(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_50)
static void C_ccall f_50(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_47)
static void C_ccall f_47(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_34)
static void C_ccall f_34(C_word c,C_word t0,C_word t1,C_word t2,...) C_noret;
C_noret_decl(f_34)
static void C_ccall f_34r(C_word t0,C_word t1,C_word t2,C_word t4) C_noret;

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

C_noret_decl(tr3r)
static void C_fcall tr3r(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3r(C_proc3 k){
int n;
C_word *a,t3;
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
n=C_rest_count(0);
a=C_alloc(n*3);
t3=C_restore_rest(a,n);
(k)(t0,t1,t2,t3);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_main_entry_point
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("toplevel"));
C_resize_stack(131072);
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(50)){
C_save(t1);
C_rereclaim2(50*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,5);
lf[0]=C_h_intern(&lf[0],3,"sum");
lf[1]=C_h_intern(&lf[1],1,"+");
lf[2]=C_h_intern(&lf[2],25,"\003sysimplicit-exit-handler");
lf[3]=C_h_intern(&lf[3],7,"newline");
lf[4]=C_h_intern(&lf[4],7,"display");
C_register_lf2(lf,5,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_17,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k15 */
static void C_ccall f_17(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_17,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_20,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k18 in k15 */
static void C_ccall f_20(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_20,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_23,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_data_structures_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k21 in k18 in k15 */
static void C_ccall f_23(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_23,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_26,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_ports_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k24 in k21 in k18 in k15 */
static void C_ccall f_26(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_26,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_29,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_extras_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_29(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_29,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_32,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_srfi_69_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_32(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word ab[9],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_32,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1 /* (set! sum ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_34,a[2]=((C_word)li0),tmp=(C_word)a,a+=3,tmp));
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_41,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t4=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_54,a[2]=t3,tmp=(C_word)a,a+=3,tmp);
C_trace("cc-gen-a.ss: 12   sum");
((C_proc9)C_retrieve_symbol_proc(lf[0]))(9,*((C_word*)lf[0]+1),t4,C_fix(3),C_fix(4),C_fix(5),C_fix(6),C_fix(7),C_fix(8),C_fix(9));}

/* k52 in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_54(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("cc-gen-a.ss: 12   display");
((C_proc3)C_retrieve_proc(*((C_word*)lf[4]+1)))(3,*((C_word*)lf[4]+1),((C_word*)t0)[2],t1);}

/* k39 in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_41(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_41,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_44,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_trace("cc-gen-a.ss: 12   newline");
((C_proc2)C_retrieve_proc(*((C_word*)lf[3]+1)))(2,*((C_word*)lf[3]+1),t2);}

/* k42 in k39 in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_44(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word ab[6],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_44,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_47,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_50,a[2]=t2,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#implicit-exit-handler");
((C_proc2)C_retrieve_symbol_proc(lf[2]))(2,*((C_word*)lf[2]+1),t3);}

/* k48 in k42 in k39 in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_50(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=t1;
((C_proc2)C_retrieve_proc(t2))(2,t2,((C_word*)t0)[2]);}

/* k45 in k42 in k39 in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_47(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* sum in k30 in k27 in k24 in k21 in k18 in k15 */
static void C_ccall f_34(C_word c,C_word t0,C_word t1,C_word t2,...){
C_word tmp;
C_word t3;
va_list v;
C_word *a,c2=c;
C_save_rest(t2,c2,3);
if(c<3) C_bad_min_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_demand(c*C_SIZEOF_PAIR+0)){
C_save_and_reclaim((void*)tr3r,(void*)f_34r,3,t0,t1,t2);}
else{
a=C_alloc((c-3)*3);
t3=C_restore_rest(a,C_rest_count(0));
f_34r(t0,t1,t2,t3);}}

static void C_ccall f_34r(C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_apply(5,0,t1,*((C_word*)lf[1]+1),t2,t3);}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[14] = {
{"toplevel:cc_gen_a_ss",(void*)C_toplevel},
{"f_17:cc_gen_a_ss",(void*)f_17},
{"f_20:cc_gen_a_ss",(void*)f_20},
{"f_23:cc_gen_a_ss",(void*)f_23},
{"f_26:cc_gen_a_ss",(void*)f_26},
{"f_29:cc_gen_a_ss",(void*)f_29},
{"f_32:cc_gen_a_ss",(void*)f_32},
{"f_54:cc_gen_a_ss",(void*)f_54},
{"f_41:cc_gen_a_ss",(void*)f_41},
{"f_44:cc_gen_a_ss",(void*)f_44},
{"f_50:cc_gen_a_ss",(void*)f_50},
{"f_47:cc_gen_a_ss",(void*)f_47},
{"f_34:cc_gen_a_ss",(void*)f_34},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}
/* end of file */
