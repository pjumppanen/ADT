Plan_1 := AdtArrayPlan.create(1,ix+1-(1));

Plan_1.create(_MemAllocator, A1_B);

zero(A1_B);

Plan_1.create(_MemAllocator, A1_C);

zero(A1_C);

Plan_1.create(_MemAllocator, A1_L);

zero(A1_L);

Plan_1.create(_MemAllocator, A1_F);

zero(A1_F);

Plan_1.create(_MemAllocator, A1_UC);

zero(A1_UC);

Plan_1.create(_MemAllocator, A1_UL);

zero(A1_UL);

Plan_1.create(_MemAllocator, A1_US);

zero(A1_US);

Plan_2 := AdtArrayPlan.create(1,1+ix+1-(1));

Plan_2.create(_MemAllocator, A1_I);

R_to_ADlib(arg_A1_I, A1_I);

Plan_1.create(_MemAllocator, A1_D);

R_to_ADlib(arg_A1_D, A1_D);

Plan_3 := AdtArrayPlan.create(1,1+ix+1-(1),-1,iy+1-(-1));

Plan_3.create(_MemAllocator, A2_IA);

R_to_ADlib(arg_A2_IA, A2_IA);

Plan_4 := AdtArrayPlan.create(-1,iy+1-(-1),1,1+ix+1-(1));

Plan_4.create(_MemAllocator, A2_IB);

R_to_ADlib(arg_A2_IB, A2_IB);

