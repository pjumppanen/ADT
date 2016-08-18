TYPE ar6 = ARRAY[ 1..6] OF DOUBLE;

PROCEDURE subd(
  n, p,q,F: DOUBLE;
  VAR an, bn: ar6);

{          Compute derivatives of an and bn with respect to p and/or q when n > 1 }

VAR t2, t3, t5, t7, t8, t9, t10, t11, t12, t13, t14, t15, t17, t19, t20, t22, t23, t24, t27, t28, t30,
  t32, t33, t36, t37, t38, t39, t41, t43, t47, t49, t50, t51, t52, t54, t55, t57, t59, t62, t63, t65,
  t69, t70, t73, t74, t76, t79, t81, t82, t84, t89, t91, t92, t96, t97, t98, t100, t102, t104, t105,
  t107, t108, t110, t113, t116, t117, t118, t119, t120, t122, t123, t126, t132, t133, t135, t136, t137,
  t138, t139, t141, t142, t143, t144, t145, t149, t151, t152, t155, t156, t161, t162, t163, t164, t165,
  t167, t172, t175, t179, t181, t182, t184, t186, t192, t198, t199, t200, t201, t207, t210, t211, t216,
  t217, t218, t220, t222, t229, t230, t231, t232, t233, t234, t236, t241, t242, t243, t245, t251, t256,
  t257, t258, t267, t268, t269, t270, t271, t272, t276, t277, t278, t279, t281, t286, t287, t288, t292,
  t293, t294, t295, t296, t297, t299, t304, t305, t308, t309, t311, t315, t317, t319, t320, t321, t322,
  t323, t324, t328, t329, t330, t336, t337, t340, t341, t343, t350, t357, t358, t363, t364, t367, t368,
  t378, t383, t384, t387, t388, t390, t397, t410, t413, t414, t422, t425, t426, t436, t440, t449, t456,
  t458, t468, t469, t477, t479, t485, t489, t492, t500, t507, t512, t517, t521, t526, t527, t528, t531,
  t532, t533, t537, t538, t540, t541, t544, t546, t548, t550, t551, t552, t553, t554, t555, t557, t559,
  t562, t563, t564, t567, t568, t572, t574, t578, t580, t582, t583, t598, t608, t610: DOUBLE;
BEGIN
  t2:=  SQR( F);
  t3:=  2*n-2;
  t5:=  p*q;
  t7:=  1/(t3*q+t5);
  t8:=  t2*t7;
  t9:=  SQR(n);
  t10:=  SQR(t9);
  t11:=  t2*t10;
  t12:=  4*n-2;
  t13:=  SQR(q);
  t14:=  t12*t13;
  t15:=  p*t13;
  t17:=  1/(t14+2*t15);
  t19:=  t9*n;
  t20:=  t19*t2;
  t22:=  1/(p+2*n-1);
  t23:=  t20*t22;
  t24:=  2*n-1;
  t27:=  1/(t24*q+t5);
  t28:=  t20*t27;
  t30:=  t10*n*t2;
  t32:=  n*t2;
  t33:=  2*n-3;
  t36:=  1/(t33*t13+t15);
  t37:=  t32*t36;
  t38:=  t9*t2;
  t39:=  1/t13;
  t41:=  t32*t39;
  t43:=  (-8+4*n)*n;
  t47:=  1/(4+t43+(4*n-4+p)*p);
  t49:=  t38*t17;
  t50:=  t38*t47;
  t51:=  t20*t47;
  t52:=  1/q;
  t54:=  t2*t47;
  t55:=  t32*t47;
  t57:=  1/(2*p+4*n-6);
  t59:=  4*t8-3*t11*t17-4*t23-t28-4*t30*t27+9*t37-t38*t39+t41+4*t11*t47-t49+24*t50-16*t51-t2*t52+4*t54-16*t55-53*t38*t57;
  t62:=  1/(p+2*n-2);
  t63:=  t32*t62;
  t65:=  1/(2*p+4*n-2);
  t69:=  t2/(p+2*n-3);
  t70:=  t69*t19;
  t73:=  1/(t3*t13+t15);
  t74:=  t11*t73;
  t76:=  t10*t9*t2;
  t79:=  1/(t24*t13+t15);
  t81:=  t2*t62;
  t82:=  4+t43;
  t84:=  4*n-4;
  t89:=  1/(t82*t13+(t84*t13+t15)*p);
  t91:=  t20*t36;
  t92:=  t11*t27;
  t96:=  t20*t89;
  t97:=  t20*t7;
  t98:=  t12*q;
  t100:=  1/(t98+2*t5);
  t102:=  51*t32*t57-24*t63+5*t38*t65+12*t70+40*t74+2*t76*t79+8*t81+4*t76*t89+52*t91+6*t92-2*t69*t10-8*t20*t62+2*t11*t22-16*t96-64*t97+t32*t100;
  t104:=  t38*t62;
  t105:=  t30*t36;
  t107:=  4*n-6;
  t108:=  t107*q;
  t110:=  1/(t108+2*t5);
  t113:=  t38*t73;
  t116:=  1/(t33*q+t5);
  t117:=  t11*t116;
  t118:=  t20*t116;
  t119:=  t30*t79;
  t120:=  t32*t73;
  t122:=  t20*t73;
  t123:=  t20*t79;
  t126:=  24*t104+14*t105+t32*t52+87*t32*t110-9*t69-12*t30*t73+24*t113-26*t117+65*t118-2*t119-4*t120+4*t30*t116-48*t122+2*t123-2*t76*t36-3*t38*t100;
  t132:=  1/(t82*q+(t84*q+t5)*p);
  t133:=  t20*t132;
  t135:=  t38*t89;
  t136:=  t11*t89;
  t137:=  t30*t89;
  t138:=  t11*t132;
  t139:=  t107*t13;
  t141:=  1/(t139+2*t15);
  t142:=  t38*t141;
  t143:=  t32*t132;
  t144:=  t32*t7;
  t145:=  t38*t7;
  t149:=  t38*t132;
  t151:=  t2*t116;
  t152:=  -48*t133-8*t30*t132+4*t135+24*t136-16*t137+32*t138-69*t142-8*t143-32*t144+72*t145-t32*t65+20*t11*t7-77*t11*t141+32*t149-155*t38*t110-9*t151;
  t155:=  t84*n;
  t156:=  1+t155;
  t161:=  1/(t156*t13+(t14+t15)*p);
  t162:=  t30*t161;
  t163:=  -8+8*n;
  t164:=  t163*n;
  t165:=  2+t164;
  t167:=  -4+8*n;
  t172:=  1/(t165*t13+(t167*t13+2*t15)*p);
  t175:=  (-24+8*n)*n;
  t179:=  1/(18+t175+(-12+8*n+2*p)*p);
  t181:=  t20*t161;
  t182:=  t38*t22;
  t184:=  (24+t175)*n;
  t186:=  (-24+12*n)*n;
  t192:=  1/(-8+t184+(12+t186+(-6+6*n+p)*p)*p);
  t198:=  1/(t156*q+(t98+t5)*p);
  t199:=  t11*t198;
  t200:=  t20*t192;
  t201:=  -4*t8+2*t162+3*t11*t172-51*t32*t179+2*t23+4*t28-2*t181-3*t182-8*t11*t192-6*t199+32*t200-6*t37;
  t207:=  1/(t165*q+(t167*q+2*t5)*p);
  t210:=  (-12+4*n)*n;
  t211:=  9+t210;
  t216:=  1/(t211*t13+(t139+t15)*p);
  t217:=  t32*t216;
  t218:=  -8+t184;
  t220:=  12+t186;
  t222:=  -6+6*n;
  t229:=  1/(t218*t13+(t220*t13+(t222*t13+t15)*p)*p);
  t230:=  t11*t229;
  t231:=  t20*t216;
  t232:=  t69*n;
  t233:=  t30*t216;
  t234:=  18+t175;
  t236:=  -12+8*n;
  t241:=  1/(t234*t13+(t236*t13+2*t15)*p);
  t242:=  t38*t241;
  t243:=  3*t38*t207-36*t50+12*t51-12*t54-9*t217+36*t55+12*t63-48*t230-52*t231-13*t232-14*t233+69*t242;
  t245:=  t32*t192;
  t251:=  1/(t234*q+(t236*q+2*t5)*p);
  t256:=  1/(1+t155+(4*n-2+p)*p);
  t257:=  t20*t256;
  t258:=  32*t245-2*t70-10*t74-6*t81-22*t91-4*t92+60*t96+16*t97-6*t104-87*t32*t251-2*t105+4*t257;
  t267:=  1/(t218*q+(t220*q+(t222*q+t5)*p)*p);
  t268:=  t11*t267;
  t269:=  t11*t79;
  t270:=  t30*t229;
  t271:=  t32*t267;
  t272:=  6*t69-64*t268-18*t113+4*t117-20*t118-t269+32*t270+2*t119+4*t120+24*t122-2*t123+16*t271;
  t276:=  t32*t27;
  t277:=  t69*t9;
  t278:=  t38*t116;
  t279:=  t38*t192;
  t281:=  77*t11*t241-t276+88*t133-28*t135-52*t136+16*t137+9*t277+35*t278-28*t138-48*t279+40*t143+155*t38*t251;
  t286:=  1/(t211*q+(t108+t5)*p);
  t287:=  t20*t286;
  t288:=  t2*t192;
  t292:=  1/(9+t210+(4*n-6+p)*p);
  t293:=  t2*t292;
  t294:=  t2*t286;
  t295:=  t20*t267;
  t296:=  t2*t132;
  t297:=  t32*t89;
  t299:=  24*t144-36*t145-96*t149-65*t287+6*t151-8*t288+9*t293+9*t294+96*t295-4*t296+4*t297-4*t30*t286;
  t304:=  t11*t286;
  t305:=  t32*t116;
  t308:=  t38*t267;
  t309:=  t11*t36;
  t311:=  t38*t79;
  t315:=  1/(2+t164+(-4+8*n+2*p)*p);
  t317:=  2*t11*t292-t32*t207-2*t11*t256+26*t304-25*t305+4*t30*t198+16*t30*t267-64*t308+11*t309-8*t76*t229+t311-5*t38*t315;
  t319:=  t32*t22;
  t320:=  t20*t198;
  t321:=  t20*t292;
  t322:=  t38*t229;
  t323:=  t38*t27;
  t324:=  t20*t229;
  t328:=  t38*t36;
  t329:=  t38*t172;
  t330:=  t32*t315+t319+t320-12*t321-8*t322+t323+32*t324-2*t76*t161+2*t76*t216+53*t38*t179+19*t328+t329;
  t336:=  (6+t236*n)*n;
  t337:=  -1+t336;
  t340:=  (-12+12*n)*n;
  t341:=  3+t340;
  t343:=  -3+6*n;
  t350:=  1/(t337*t13+(t341*t13+(t343*t13+t15)*p)*p);
  t357:=  (-64+(96+(-64+16*n)*n)*n)*n;
  t358:=  16+t357;
  t363:=  (96+(-96+32*n)*n)*n;
  t364:=  -32+t363;
  t367:=  (-48+24*n)*n;
  t368:=  24+t367;
  t378:=  1/(t358*q+(t364*q+(t368*q+(t163*q+t5)*p)*p)*p);
  t383:=  (54+(-36+8*n)*n)*n;
  t384:=  -27+t383;
  t387:=  (-36+12*n)*n;
  t388:=  27+t387;
  t390:=  -9+6*n;
  t397:=  1/(t384*q+(t388*q+(t390*q+t5)*p)*p);
  t410:=  1/(t358*t13+(t364*t13+(t368*t13+(t163*t13+t15)*p)*p)*p);
  t413:=  t32*t286;
  t414:=  -3*t11*t350+2*t8-4*t162-2*t28+4*t181+t182+8*t199-288*t20*t378-32*t200+2*t37+8*t30*t397+24*t38*t410+4*t76*t350+50*t413+14*t50;
  t422:=  1/(16+t357+(-32+t363+(24+t367+(-8+8*n+p)*p)*p)*p);
  t425:=  t32*t229;
  t426:=  -96*t20*t422+14*t54+12*t217-28*t55-96*t30*t410-2*t63+128*t230+44*t231+3*t232+4*t233-96*t245-8*t425+2*t81+4*t91-52*t96;
  t436:=  1/(t337*q+(t341*q+(t343*q+t5)*p)*p);
  t440:=  12*t11*t436-4*t257-2*t69+72*t268+6*t113-18*t38*t292+2*t118+t269+144*t11*t410-40*t270-2*t120-4*t122-96*t271+t276-36*t133;
  t449:=  1/(t384*t13+(t388*t13+(t390*t13+t15)*p)*p);
  t456:=  1/(-1+t336+(3+t340+(-3+6*n+p)*p)*p);
  t458:=  38*t135+22*t136-t277-69*t38*t449-7*t278+96*t279-52*t143-8*t144+6*t145+80*t149+40*t287-2*t151+32*t288-12*t293+4*t11*t456-12*t294;
  t468:=  -224*t295+8*t296-8*t297+24*t76*t410-8*t304-52*t11*t397+7*t305+87*t32*t397+240*t308-t309-t311+104*t20*t449-8*t20*t456+5*t38*t456+t32*t436;
  t469:=  t38*t198;
  t477:=  -2*t469+26*t32*t292-t319-8*t320+4*t321+64*t322+t323-144*t324-5*t328-18*t2*t397+24*t2*t422+130*t20*t397-155*t38*t397-96*t32*t422-96*t20*t410;
  t479:=  t11*t161;
  t485:=  1/(-27+t383+(27+t387+(6*n-9+p)*p)*p);
  t489:=  t32*t198;
  t492:=  t2*t267;
  t500:=  2*t479+51*t32*t485-77*t11*t449+28*t30*t449+2*t489+18*t32*t449-2*t38*t161+8*t492-t38*t350+4*t20*t350-8*t30*t436-4*t30*t350+6*t38*t256-3*t38*t436+24*t11*t422;
  t507:=  t38*t286;
  t512:=  t11*t216;
  t517:=  -2*t32*t256-4*t11*t485-53*t38*t485+144*t38*t422+24*t20*t485-18*t2*t485-70*t507-t32*t456-48*t32*t378-48*t30*t378+192*t38*t378-22*t512+192*t11*t378-38*t38*t216-2*t20*t436-4*t76*t449;
  t521:=  16*t8-8*t28+t41-3*t49+20*t74+65*t91+4*t92-48*t96-16*t97+4*t105+72*t113-4*t117+24*t118+6*t269-4*t119-32*t120-64*t122-t123-t276-32*t133;
  t526:=  t2*t73;
  t527:=  t2*t36;
  t528:=  48*t149-18*t151+8*t296-8*t297+51*t305-26*t309+5*t323+t32*t17+87*t32*t141+4*t526-9*t527;
  t531:=  t2*t89;
  t532:=  t32*t79;
  t533:=  -32*t96+8*t136+48*t135-48*t120+24*t91+48*t113-16*t122-53*t328-18*t527-8*t123+16*t526+8*t531+5*t311-t532+51*t37-4*t309+4*t269-32*t297;
  t537:=  9*t2*t216-87*t32*t241-t32*t172-12*t8+4*t162+4*t28+t181-4*t199-25*t37-51*t413-64*t230-65*t231-4*t233+155*t242+16*t425;
  t538:=  -20*t91+88*t96-16*t268-36*t113-4*t118-4*t269+16*t270+24*t120+16*t122+4*t123+64*t271+2*t276+24*t133-96*t135-28*t136+18*t278;
  t540:=  72*t143+24*t144-12*t145-72*t149-24*t287+12*t151+18*t294+64*t295-24*t296+40*t297+4*t304-26*t305-96*t308+4*t309+t311;
  t541:=  -5*t469+8*t320-64*t322-6*t323+96*t324+35*t328+3*t329-6*t479+t489-16*t492+53*t507+26*t512-4*t526+6*t527-t532-4*t531;
  t544:=  t9*F;
  t546:=  1/(p+2*n);
  t548:=  q*n;
  t550:=  1/(t5+2*t548);
  t551:=  t544*t550;
  t552:=  t544*t7;
  t553:=  n*F;
  t554:=  t553*t7;
  t555:=  t19*F;
  t557:=  F*t62;
  t559:=  t557*n;
  t562:=  1-F+2*t544*t546-2*t551-4*t552+2*t554+2*t555*t7-2*t557-2*t557*t9+4*t559-2*t555*t550+2*t553*t52;
  t563:=  t553*t550;
  t564:=  t553*t132;
  t567:=  t544*t132;
  t568:=  F*t47;
  t572:=  1/(4*t9+(4*n+p)*p);
  t574:=  q*t9;
  t578:=  1/(4*t574+(4*t548+t5)*p);
  t580:=  t544*t578;
  t582:=  t553*t47;
  t583:=  -t563-2*t564+2*t544*t47-2*t555*t132+4*t567+2*t568-2*t544*t572+2*t555*t578-t551+2*t580+t552-t554+t557-t559+t553*t546-4*t582;
  t598:=  1/(8*q*t19+(12*t574+(6*t548+t5)*p)*p);
  t608:=  2*t564-2*t567-2*t568+2*t580+2*t553*t578+4*t544/(8*t19+(12*t9+(6*n+p)*p)*p)-4*t555*t598-2*t553*t572+8*t553*t192-4*F*t192-4*t544*t192+4*t553*t267-8*t544*t267+4*t555*t267-4*t544*t598+2*t582;
  t610:=  F*t7;
  an[1]:=  t59+t102+t126+t152;
  an[2]:=  t201+t243+t258+t272+t281+t299+t317+t330;
  an[3]:=  t414+t426+t440+t458+t468+t477+t500+t517;
  an[4]:=  t521+32*t135+32*t136-8*t137-t2*t39-53*t278+8*t138-155*t142-32*t143-48*t144+48*t145+t528;
  an[5]:=  t533;
  an[6]:=  t537+t538+t540+t541;
  bn[1]:=  t562;
  bn[2]:=  t583;
  bn[3]:=  t608;
  bn[4]:=  -F*t52-2*t552+4*t554-2*t610+2*t551;
  bn[5]:=  0;
  bn[6]:=  2*t567-t554-4*t564+t563-2*t580+t610+2*F*t132;
END;

PROCEDURE derconf(
  VAR p,q,w: DOUBLE;
  VAR n: INTEGER;
  VAR an,bn: ar6);
VAR
  F, t1, t2, t3, t4: DOUBLE;
BEGIN
{          Compute derivatives of an and bn with respect to p and/or q }

  F:=  w*q/p;
  if (n=1) then
  BEGIN
    t1:= 1-1/(p+1);
    t2:= 1-1/q;
    t3:= 1-2/(p+2);
    t4:= 1-2/q;
    an[1]:= t1*t2*F;
    an[2]:= -an[1]/(p+1);
    an[3]:= -2*an[2]/(p+1);
    an[4]:= t1*F/q;
    an[5]:= 0;
    an[6]:= -an[4]/(p+1);
    bn[1]:= 1-t3*t4*F;
    bn[2]:= t3*t4*F/(p+2);
    bn[3]:= -2*bn[2]/(p+2);
    bn[4]:= -t3*F/q;
    bn[5]:= 0;
    bn[6]:= -bn[4]/(p+2)
  END
  ELSE
    subd(n,p,q,F,an,bn);
END;

PROCEDURE inbeder(
  x,p,q: DOUBLE;
  psi, der : PDOUBLE_ARRAY;
  VAR nappx, ifault: INTEGER;
  VAR errapx: DOUBLE);
{C
C             x: Input argument -- value to which beta function is integrated
C             p,q: Input arguments -- beta shape parameters
C             psi: input arguments -- vector of length 7
C                                    psi[1]:=  log[Beta(p,q)]
C                                    psi[2]:=  digamma[p]
C                                    psi[3]:=  trigamma[p]
C                                    psi[4]:=  digamma[q]
C                                    psi[5]:=  trigamma[q]
C                                    psi[6]:=  digamma(p+q)
C                                    psi[7]:=  trigamma(p+q)
C             der: output -- vector of length 6
C                            der[1]:=  I (incomplete beta function)
C                            der[2]:=  Ip
C                            der[3] ::=   Ipp
C                            der[4]:=  Iq
C                            der[5]:=  Iqq
C                            der[6]:=  Ipq
C             nappx: output -- highest order approximant evaluated
C             errapx: output -- approximate size of maximum absolute error
C                               of computed derivatives
C             ifault: output -- error indicator
C                               ifault:=  0: no error
C                               ifault:=  1: x outside of (0,1)
C                               ifault:=  2: p less that 0
C                               ifault:=  3: q less than 0
C                               ifault:=  4: derivatives set to 0 because I:= 0
C                                           or I:= 1
C                               ifault:=  5: evaluation stopped after maxappx
C                                           terms
C}

VAR pa,pb,pab,pa1,pb1,pab1,
  pp,qq,x1,logx1,logomx,
  w,omx,Rn,pr,d,d1,c0,prmax,e: DOUBLE;
  c,dr,an1,an2,bn1,bn2,an,bn,dan,dbn,der_old: ar6;
  i, ii, iii, n: INTEGER;

CONST
  err=1E-12;
  maxappx = 200;
  minappx = 3;
  prmin = 1E-24;
BEGIN
  prmax:= 1-err;

{          Initialize derivative vectors
      and check for admissability of input arguments }

  FOR i:= 1 TO 6 DO
  BEGIN
    der_old[i]:= 0;
    c[i]:= 0;
    dr[i]:= 1;
    der[i]:= 0;
    an2[i]:= 0;
    bn2[i]:= 0;
    an1[i]:= 0;
    bn1[i]:= 0;
  END;

  an1[1]:= 1;
  bn1[1]:= 1;
  an2[1]:= 1;
  pab:= psi[6];
  pab1:= psi[7];
  ifault:= 0;
  nappx:= 0;

  if (x<=0) OR (x>=1) then
  ifault:= 1
  ELSE IF p<=0 then
    ifault:= 2
  ELSE if q<=0 then
  ifault:= 3;

  IF ifault<>0 THEN
EXIT;

{          Use I(x,p,q):=  1- I(1-x,q,p) if x > p/(p+q) }

  if (x<=p/(p+q)) then
  BEGIN
    ii:= 1;
    x1:= x;
    omx:= 1-x;
    pp:= p;
    qq:= q;
    pa:= psi[2];
    pb:= psi[4];
    pa1:= psi[3];
    pb1:= psi[5];
  END
  ELSE
  BEGIN
    ii:= 2;
    x1:= 1-x;
    omx:= x;
    pp:= q;
    qq:= p;
    pa:= psi[4];
    pb:= psi[2];
    pa1:= psi[5];
    pb1:= psi[3];
  END;

  w:= x1/omx;
  logx1:= LN(x1);
  logomx:= LN(omx);

{          Compute derivatives of K(x,p,q):=  x^p(1-x)^(q-1)/[p beta(p,q)] }

  c[1]:= pp*logx1+(qq-1)*logomx-psi[1]-LN(pp);
  c0:= exp(c[1]);
  c[2]:= logx1-1/pp-pa+pab;
  c[3]:= SQR( c[2])+1/SQR(pp)-pa1+pab1;
  c[4]:= logomx-pb+pab;
  c[5]:= SQR( c[4])-pb1+pab1;
  c[6]:= c[2]*c[4]+pab1;

{          Set counter and begin iteration  }


  n:= 0;
  REPEAT
    n:= n+1;
  
{            Compute derivatives of an and bn with respect to p and/or q }

    derconf(pp,qq,w,n,an,bn);
  
{            Use forward recurrance relations to compute An, Bn,
        and their derivatives }
  
    dan[1]:= an[1]*an2[1]+bn[1]*an1[1];
    dbn[1]:= an[1]*bn2[1]+bn[1]*bn1[1];
    dan[2]:= an[2]*an2[1]+an[1]*an2[2]+bn[2]*an1[1]+bn[1]*an1[2];
    dbn[2]:= an[2]*bn2[1]+an[1]*bn2[2]+bn[2]*bn1[1]+bn[1]*bn1[2];
    dan[3]:= an[3]*an2[1]+2*an[2]*an2[2]+an[1]*an2[3]+bn[3]*an1[1]
        +2*bn[2]*an1[2]+bn[1]*an1[3];
    dbn[3]:= an[3]*bn2[1]+2*an[2]*bn2[2]+an[1]*bn2[3]+bn[3]*bn1[1]
        +2*bn[2]*bn1[2]+bn[1]*bn1[3];
    dan[4]:= an[4]*an2[1]+an[1]*an2[4]+bn[4]*an1[1]+bn[1]*an1[4];
    dbn[4]:= an[4]*bn2[1]+an[1]*bn2[4]+bn[4]*bn1[1]+bn[1]*bn1[4];
    dan[5]:= an[5]*an2[1]+2*an[4]*an2[4]+an[1]*an2[5]+bn[5]*an1[1]
        +2*bn[4]*an1[4]+bn[1]*an1[5];
    dbn[5]:= an[5]*bn2[1]+2*an[4]*bn2[4]+an[1]*bn2[5]+bn[5]*bn1[1]
        +2*bn[4]*bn1[4]+bn[1]*bn1[5];
    dan[6]:= an[6]*an2[1]+an[2]*an2[4]+an[4]*an2[2]+an[1]*an2[6]
        +bn[6]*an1[1]+bn[2]*an1[4]+bn[4]*an1[2]+bn[1]*an1[6];
    dbn[6]:= an[6]*bn2[1]+an[2]*bn2[4]+an[4]*bn2[2]+an[1]*bn2[6]
        +bn[6]*bn1[1]+bn[2]*bn1[4]+bn[4]*bn1[2]+bn[1]*bn1[6];
  
{          Scale derivatives to prevent overflow }
  
    Rn:= dan[1];
    iii:= 1;
    IF (abs(dbn[1])>abs(dan[1])) then
    BEGIN
      Rn:= dbn[1];
      iii:= 2;
    END;
        
    an1[1]:= an1[1]/Rn;
    bn1[1]:= bn1[1]/Rn;
    FOR i:= 2 TO 6 DO
    BEGIN
      an1[i]:= an1[i]/Rn;
      bn1[i]:= bn1[i]/Rn;
      dan[i]:= dan[i]/Rn;
      dbn[i]:= dbn[i]/Rn;
    END;
        
    if (iii=1) then
    BEGIN
      dbn[1]:= dbn[1]/dan[1];
      dan[1]:= 1;
    END
    ELSE BEGIN
      dan[1]:= dan[1]/dbn[1];
      dbn[1]:= 1;
    END;
  
{          Compute components of derivatives of the nth approximant }
  
    dr[1]:= dan[1]/dbn[1];
    Rn:=  dr[1];
    dr[2]:=  (dan[2]-Rn*dbn[2])/dbn[1];
    dr[3]:=  (-2*dan[2]*dbn[2]+2*Rn*SQR(dbn[2]))/SQR(dbn[1])+(dan[3]-Rn*dbn[3])/dbn[1];
    dr[4]:=  (dan[4]-Rn*dbn[4])/dbn[1];
    dr[5]:=  (-2*dan[4]*dbn[4]+2*Rn*SQR(dbn[4]))/SQR(dbn[1])+(dan[5]-Rn*dbn[5])/dbn[1];
    dr[6]:=  (-dan[2]*dbn[4]-dan[4]*dbn[2]+2*Rn*dbn[2]*dbn[4])/SQR(dbn[1])+(dan[6]-Rn*dbn[6])/dbn[1];

{          Save terms corresponding to approximants n-1 and n-2 }

    an2:= an1; an1:= dan;
    bn2:= bn1; bn1:= dbn;

{          Check if I < prmin or I > prmax }
  
    if (dr[1]>0) then
      pr:= exp(c[1]+LN(dr[1]))
    else
      pr:= 0;

    der[1]:= pr;
    if ((pr<prmin) or (pr>prmax)) then
    BEGIN
      errapx:=  abs(der_old[1]-pr);
      if (errapx<=err) then
      BEGIN
        ifault:= 4;
        FOR i:= 2 TO 6 DO
          der[i]:= 0;
  BREAK;  
      END;
    END;

{          Compute nth approximants }
  
    der[2]:= pr*c[2]+c0*dr[2];
    der[3]:= pr*c[3]+2*c0*c[2]*dr[2]+c0*dr[3];
    der[4]:= pr*c[4]+c0*dr[4];
    der[5]:= pr*c[5]+2*c0*c[4]*dr[4]+c0*dr[5];
    der[6]:= pr*c[6]+c0*c[4]*dr[2]+c0*c[2]*dr[4]+c0*dr[6];
  
{          Check for convergence, check for maximum and minimum iterations. }
            
    d:= 0;
    errapx:= 0;
    FOR i:= 1 TO 6 DO
    BEGIN
      d1:= math. max(err,abs(der[i]));
      e:= abs(der_old[i]-der[i]);
      d1:= e/d1;
      if (d1>d) THEN
        d:= d1;
      if (e>errapx) THEN 
        errapx:= e;
      der_old[i]:= der[i];
    END;
        
    if (n<minappx) THEN
      d:= 1;
    if (n>=maxappx) then
    BEGIN
      d:= 0;
      ifault:= 5;
    END;
  UNTIL d<err;

{          Adjust results if I(x,p,q):=  1- I(1-x,q,p) was used }

  if (ii=2) then
  BEGIN
    der[1]:= 1-der[1];
    c0:= der[2];
    der[2]:= -der[4];
    der[4]:= -c0;
    c0:= der[3];
    der[3]:= -der[5];
    der[5]:= -c0;
    der[6]:= -der[6];
  END;
      
  nappx:= n;
END;

