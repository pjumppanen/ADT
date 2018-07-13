Plan_1.initialise(1,nfleets+1-(1),1,nareas+1-(1),1,nsubyears+1-(1),1,nsim +1-(1));

Plan_1.create(MemAllocator, EforYear);

zero(EforYear);

Plan_2.initialise(1,nages+1-(1),1,npop+1-(1),1,nsim +1-(1));

Plan_2.create(MemAllocator, surv);

zero(surv);

Plan_3.initialise(1,npop+1-(1),1,nsim +1-(1));

Plan_3.create(MemAllocator, B0);

zero(B0);

Plan_3.create(MemAllocator, SSB0);

zero(SSB0);

Plan_3.create(MemAllocator, SSBpR);

zero(SSBpR);

Plan_3.create(MemAllocator, aR);

zero(aR);

Plan_3.create(MemAllocator, bR);

zero(bR);

Plan_4.initialise(1,nfleets+1-(1),1,nsim +1-(1));

Plan_4.create(MemAllocator, FM);

zero(FM);

Plan_5.initialise(1,nareas+1-(1),1,nsim +1-(1));

Plan_5.create(MemAllocator, MovN);

zero(MovN);

Plan_6.initialise(1,nareas+1-(1),1,npop+1-(1),1,nsim +1-(1));

Plan_6.create(MemAllocator, MSY_RecSpatialDevs);

zero(MSY_RecSpatialDevs);

Plan_7.initialise(1,nsubyears +1-(1));

Plan_7.create(MemAllocator, Recsubyr);

AdtArrayPlanActor::R_to_ADlib(MemAllocator, (char*)arg_Recsubyr, (char*)Recsubyr);

