
farm.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <start_farm>:
   0:	55                   	push   %rbp
   1:	48 89 e5             	mov    %rsp,%rbp
   4:	b8 01 00 00 00       	mov    $0x1,%eax
   9:	5d                   	pop    %rbp
   a:	c3                   	retq   

000000000000000b <addval_476>:
   b:	55                   	push   %rbp
   c:	48 89 e5             	mov    %rsp,%rbp
   f:	89 7d fc             	mov    %edi,-0x4(%rbp)
  12:	8b 45 fc             	mov    -0x4(%rbp),%eax
  15:	2d b8 76 38 3c       	sub    $0x3c3876b8,%eax
  1a:	5d                   	pop    %rbp
  1b:	c3                   	retq   

000000000000001c <getval_364>:
  1c:	55                   	push   %rbp
  1d:	48 89 e5             	mov    %rsp,%rbp
  20:	b8 2a 58 90 90       	mov    $0x9090582a,%eax
  25:	5d                   	pop    %rbp
  26:	c3                   	retq   

0000000000000027 <getval_331>:
  27:	55                   	push   %rbp
  28:	48 89 e5             	mov    %rsp,%rbp
  2b:	b8 48 89 c7 c1       	mov    $0xc1c78948,%eax
  30:	5d                   	pop    %rbp
  31:	c3                   	retq   

0000000000000032 <setval_355>:
  32:	55                   	push   %rbp
  33:	48 89 e5             	mov    %rsp,%rbp
  36:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  3a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  3e:	c7 00 d8 90 90 c3    	movl   $0xc39090d8,(%rax)
  44:	90                   	nop
  45:	5d                   	pop    %rbp
  46:	c3                   	retq   

0000000000000047 <setval_379>:
  47:	55                   	push   %rbp
  48:	48 89 e5             	mov    %rsp,%rbp
  4b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  4f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  53:	c7 00 23 4c 89 c7    	movl   $0xc7894c23,(%rax)
  59:	90                   	nop
  5a:	5d                   	pop    %rbp
  5b:	c3                   	retq   

000000000000005c <addval_290>:
  5c:	55                   	push   %rbp
  5d:	48 89 e5             	mov    %rsp,%rbp
  60:	89 7d fc             	mov    %edi,-0x4(%rbp)
  63:	8b 45 fc             	mov    -0x4(%rbp),%eax
  66:	2d 75 a7 6f 3c       	sub    $0x3c6fa775,%eax
  6b:	5d                   	pop    %rbp
  6c:	c3                   	retq   

000000000000006d <getval_494>:
  6d:	55                   	push   %rbp
  6e:	48 89 e5             	mov    %rsp,%rbp
  71:	b8 48 89 c7 c3       	mov    $0xc3c78948,%eax
  76:	5d                   	pop    %rbp
  77:	c3                   	retq   

0000000000000078 <setval_437>:
  78:	55                   	push   %rbp
  79:	48 89 e5             	mov    %rsp,%rbp
  7c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  80:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  84:	c7 00 94 d8 90 c3    	movl   $0xc390d894,(%rax)
  8a:	90                   	nop
  8b:	5d                   	pop    %rbp
  8c:	c3                   	retq   

000000000000008d <mid_farm>:
  8d:	55                   	push   %rbp
  8e:	48 89 e5             	mov    %rsp,%rbp
  91:	b8 01 00 00 00       	mov    $0x1,%eax
  96:	5d                   	pop    %rbp
  97:	c3                   	retq   

0000000000000098 <add_xy>:
  98:	55                   	push   %rbp
  99:	48 89 e5             	mov    %rsp,%rbp
  9c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  a0:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  a4:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  a8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  ac:	48 01 d0             	add    %rdx,%rax
  af:	5d                   	pop    %rbp
  b0:	c3                   	retq   

00000000000000b1 <setval_148>:
  b1:	55                   	push   %rbp
  b2:	48 89 e5             	mov    %rsp,%rbp
  b5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  b9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  bd:	c7 00 09 ca 90 c3    	movl   $0xc390ca09,(%rax)
  c3:	90                   	nop
  c4:	5d                   	pop    %rbp
  c5:	c3                   	retq   

00000000000000c6 <getval_349>:
  c6:	55                   	push   %rbp
  c7:	48 89 e5             	mov    %rsp,%rbp
  ca:	b8 48 89 e0 c1       	mov    $0xc1e08948,%eax
  cf:	5d                   	pop    %rbp
  d0:	c3                   	retq   

00000000000000d1 <addval_194>:
  d1:	55                   	push   %rbp
  d2:	48 89 e5             	mov    %rsp,%rbp
  d5:	89 7d fc             	mov    %edi,-0x4(%rbp)
  d8:	8b 45 fc             	mov    -0x4(%rbp),%eax
  db:	2d f7 3e c7 3f       	sub    $0x3fc73ef7,%eax
  e0:	5d                   	pop    %rbp
  e1:	c3                   	retq   

00000000000000e2 <addval_335>:
  e2:	55                   	push   %rbp
  e3:	48 89 e5             	mov    %rsp,%rbp
  e6:	89 7d fc             	mov    %edi,-0x4(%rbp)
  e9:	8b 45 fc             	mov    -0x4(%rbp),%eax
  ec:	2d 78 3e df 2d       	sub    $0x2ddf3e78,%eax
  f1:	5d                   	pop    %rbp
  f2:	c3                   	retq   

00000000000000f3 <getval_100>:
  f3:	55                   	push   %rbp
  f4:	48 89 e5             	mov    %rsp,%rbp
  f7:	b8 89 d6 c4 db       	mov    $0xdbc4d689,%eax
  fc:	5d                   	pop    %rbp
  fd:	c3                   	retq   

00000000000000fe <getval_316>:
  fe:	55                   	push   %rbp
  ff:	48 89 e5             	mov    %rsp,%rbp
 102:	b8 89 d6 28 d2       	mov    $0xd228d689,%eax
 107:	5d                   	pop    %rbp
 108:	c3                   	retq   

0000000000000109 <addval_107>:
 109:	55                   	push   %rbp
 10a:	48 89 e5             	mov    %rsp,%rbp
 10d:	89 7d fc             	mov    %edi,-0x4(%rbp)
 110:	8b 45 fc             	mov    -0x4(%rbp),%eax
 113:	2d 61 95 76 29       	sub    $0x29769561,%eax
 118:	5d                   	pop    %rbp
 119:	c3                   	retq   

000000000000011a <addval_320>:
 11a:	55                   	push   %rbp
 11b:	48 89 e5             	mov    %rsp,%rbp
 11e:	89 7d fc             	mov    %edi,-0x4(%rbp)
 121:	8b 45 fc             	mov    -0x4(%rbp),%eax
 124:	2d 07 bf 76 1f       	sub    $0x1f76bf07,%eax
 129:	5d                   	pop    %rbp
 12a:	c3                   	retq   

000000000000012b <addval_414>:
 12b:	55                   	push   %rbp
 12c:	48 89 e5             	mov    %rsp,%rbp
 12f:	89 7d fc             	mov    %edi,-0x4(%rbp)
 132:	8b 45 fc             	mov    -0x4(%rbp),%eax
 135:	05 89 c1 c7 67       	add    $0x67c7c189,%eax
 13a:	5d                   	pop    %rbp
 13b:	c3                   	retq   

000000000000013c <addval_205>:
 13c:	55                   	push   %rbp
 13d:	48 89 e5             	mov    %rsp,%rbp
 140:	89 7d fc             	mov    %edi,-0x4(%rbp)
 143:	8b 45 fc             	mov    -0x4(%rbp),%eax
 146:	2d 77 3e cf 3f       	sub    $0x3fcf3e77,%eax
 14b:	5d                   	pop    %rbp
 14c:	c3                   	retq   

000000000000014d <setval_457>:
 14d:	55                   	push   %rbp
 14e:	48 89 e5             	mov    %rsp,%rbp
 151:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 155:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 159:	c7 00 89 d6 90 90    	movl   $0x9090d689,(%rax)
 15f:	90                   	nop
 160:	5d                   	pop    %rbp
 161:	c3                   	retq   

0000000000000162 <addval_261>:
 162:	55                   	push   %rbp
 163:	48 89 e5             	mov    %rsp,%rbp
 166:	89 7d fc             	mov    %edi,-0x4(%rbp)
 169:	8b 45 fc             	mov    -0x4(%rbp),%eax
 16c:	2d 31 b7 f6 1f       	sub    $0x1ff6b731,%eax
 171:	5d                   	pop    %rbp
 172:	c3                   	retq   

0000000000000173 <setval_311>:
 173:	55                   	push   %rbp
 174:	48 89 e5             	mov    %rsp,%rbp
 177:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 17b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 17f:	c7 00 89 ca 91 90    	movl   $0x9091ca89,(%rax)
 185:	90                   	nop
 186:	5d                   	pop    %rbp
 187:	c3                   	retq   

0000000000000188 <setval_382>:
 188:	55                   	push   %rbp
 189:	48 89 e5             	mov    %rsp,%rbp
 18c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 190:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 194:	c7 00 8d c1 08 c0    	movl   $0xc008c18d,(%rax)
 19a:	90                   	nop
 19b:	5d                   	pop    %rbp
 19c:	c3                   	retq   

000000000000019d <getval_330>:
 19d:	55                   	push   %rbp
 19e:	48 89 e5             	mov    %rsp,%rbp
 1a1:	b8 89 d6 c1 70       	mov    $0x70c1d689,%eax
 1a6:	5d                   	pop    %rbp
 1a7:	c3                   	retq   

00000000000001a8 <addval_324>:
 1a8:	55                   	push   %rbp
 1a9:	48 89 e5             	mov    %rsp,%rbp
 1ac:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1af:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1b2:	2d ba f6 29 6f       	sub    $0x6f29f6ba,%eax
 1b7:	5d                   	pop    %rbp
 1b8:	c3                   	retq   

00000000000001b9 <addval_256>:
 1b9:	55                   	push   %rbp
 1ba:	48 89 e5             	mov    %rsp,%rbp
 1bd:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1c0:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1c3:	2d 34 b7 72 1f       	sub    $0x1f72b734,%eax
 1c8:	5d                   	pop    %rbp
 1c9:	c3                   	retq   

00000000000001ca <getval_292>:
 1ca:	55                   	push   %rbp
 1cb:	48 89 e5             	mov    %rsp,%rbp
 1ce:	b8 cb 89 c1 90       	mov    $0x90c189cb,%eax
 1d3:	5d                   	pop    %rbp
 1d4:	c3                   	retq   

00000000000001d5 <addval_275>:
 1d5:	55                   	push   %rbp
 1d6:	48 89 e5             	mov    %rsp,%rbp
 1d9:	89 7d fc             	mov    %edi,-0x4(%rbp)
 1dc:	8b 45 fc             	mov    -0x4(%rbp),%eax
 1df:	2d 38 76 1f 3c       	sub    $0x3c1f7638,%eax
 1e4:	5d                   	pop    %rbp
 1e5:	c3                   	retq   

00000000000001e6 <setval_402>:
 1e6:	55                   	push   %rbp
 1e7:	48 89 e5             	mov    %rsp,%rbp
 1ea:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 1ee:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 1f2:	c7 00 09 ca 08 d2    	movl   $0xd208ca09,(%rax)
 1f8:	90                   	nop
 1f9:	5d                   	pop    %rbp
 1fa:	c3                   	retq   

00000000000001fb <setval_358>:
 1fb:	55                   	push   %rbp
 1fc:	48 89 e5             	mov    %rsp,%rbp
 1ff:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 203:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 207:	c7 00 89 d6 94 c3    	movl   $0xc394d689,(%rax)
 20d:	90                   	nop
 20e:	5d                   	pop    %rbp
 20f:	c3                   	retq   

0000000000000210 <addval_327>:
 210:	55                   	push   %rbp
 211:	48 89 e5             	mov    %rsp,%rbp
 214:	89 7d fc             	mov    %edi,-0x4(%rbp)
 217:	8b 45 fc             	mov    -0x4(%rbp),%eax
 21a:	05 89 ca c3 44       	add    $0x44c3ca89,%eax
 21f:	5d                   	pop    %rbp
 220:	c3                   	retq   

0000000000000221 <addval_365>:
 221:	55                   	push   %rbp
 222:	48 89 e5             	mov    %rsp,%rbp
 225:	89 7d fc             	mov    %edi,-0x4(%rbp)
 228:	8b 45 fc             	mov    -0x4(%rbp),%eax
 22b:	2d 78 3e c7 24       	sub    $0x24c73e78,%eax
 230:	5d                   	pop    %rbp
 231:	c3                   	retq   

0000000000000232 <getval_195>:
 232:	55                   	push   %rbp
 233:	48 89 e5             	mov    %rsp,%rbp
 236:	b8 89 ca 38 db       	mov    $0xdb38ca89,%eax
 23b:	5d                   	pop    %rbp
 23c:	c3                   	retq   

000000000000023d <setval_252>:
 23d:	55                   	push   %rbp
 23e:	48 89 e5             	mov    %rsp,%rbp
 241:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 245:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 249:	c7 00 92 8b d6 c3    	movl   $0xc3d68b92,(%rax)
 24f:	90                   	nop
 250:	5d                   	pop    %rbp
 251:	c3                   	retq   

0000000000000252 <setval_193>:
 252:	55                   	push   %rbp
 253:	48 89 e5             	mov    %rsp,%rbp
 256:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 25a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 25e:	c7 00 89 ca 28 db    	movl   $0xdb28ca89,(%rax)
 264:	90                   	nop
 265:	5d                   	pop    %rbp
 266:	c3                   	retq   

0000000000000267 <getval_375>:
 267:	55                   	push   %rbp
 268:	48 89 e5             	mov    %rsp,%rbp
 26b:	b8 48 89 e0 c3       	mov    $0xc3e08948,%eax
 270:	5d                   	pop    %rbp
 271:	c3                   	retq   

0000000000000272 <setval_103>:
 272:	55                   	push   %rbp
 273:	48 89 e5             	mov    %rsp,%rbp
 276:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 27a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 27e:	c7 00 89 c1 20 c0    	movl   $0xc020c189,(%rax)
 284:	90                   	nop
 285:	5d                   	pop    %rbp
 286:	c3                   	retq   

0000000000000287 <getval_333>:
 287:	55                   	push   %rbp
 288:	48 89 e5             	mov    %rsp,%rbp
 28b:	b8 89 ca 91 c3       	mov    $0xc391ca89,%eax
 290:	5d                   	pop    %rbp
 291:	c3                   	retq   

0000000000000292 <getval_362>:
 292:	55                   	push   %rbp
 293:	48 89 e5             	mov    %rsp,%rbp
 296:	b8 05 88 ca 90       	mov    $0x90ca8805,%eax
 29b:	5d                   	pop    %rbp
 29c:	c3                   	retq   

000000000000029d <setval_244>:
 29d:	55                   	push   %rbp
 29e:	48 89 e5             	mov    %rsp,%rbp
 2a1:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 2a5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2a9:	c7 00 48 89 e0 90    	movl   $0x90e08948,(%rax)
 2af:	90                   	nop
 2b0:	5d                   	pop    %rbp
 2b1:	c3                   	retq   

00000000000002b2 <setval_262>:
 2b2:	55                   	push   %rbp
 2b3:	48 89 e5             	mov    %rsp,%rbp
 2b6:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 2ba:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 2be:	c7 00 48 8d e0 c3    	movl   $0xc3e08d48,(%rax)
 2c4:	90                   	nop
 2c5:	5d                   	pop    %rbp
 2c6:	c3                   	retq   

00000000000002c7 <end_farm>:
 2c7:	55                   	push   %rbp
 2c8:	48 89 e5             	mov    %rsp,%rbp
 2cb:	b8 01 00 00 00       	mov    $0x1,%eax
 2d0:	5d                   	pop    %rbp
 2d1:	c3                   	retq   
