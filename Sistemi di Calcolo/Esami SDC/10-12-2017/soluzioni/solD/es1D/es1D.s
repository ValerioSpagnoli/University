# inserire la soluzione qui...

# void fetch(short u, short* p);

# void update(short* v, int n) { // v <-> esi, n <-> edi
#     int i;                     // i <-> ebx
#     short x;                   // x <-> 8(%esp)
#     for (i=0; i<n; ++i) {
#         fetch(v[i], &x);
#         v[i] = x;
#     }
# }

.globl update

update:
    pushl %esi
    pushl %edi
    pushl %ebx
    subl $12, %esp

    movl 28(%esp), %esi
    movl 32(%esp), %edi
    xorl %ebx, %ebx           # i = 0

L:  cmpl %edi, %ebx           # if (i>=n)
    jge E                     #     goto E
    movw (%esi,%ebx,2), %ax   # ax = v[i]
    movswl %ax, %eax          # eax = (int)ax  <--- integer promotion
    movl %eax, (%esp)         # pass eax as first parameter
    leal 8(%esp), %eax        # eax = &x
    movl %eax, 4(%esp)        # pass &x as second parameter
    call fetch                # fetch(v[i], &x)
    movw 8(%esp), %ax         # ax = x
    movw %ax, (%esi,%ebx,2)   # v[i] = ax
    incl %ebx                 # ++i
    jmp L                     # goto L

E:  addl $12, %esp
    popl %ebx
    popl %edi
    popl %esi
    ret
