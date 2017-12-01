Plan_5 := AdtArrayPlan.create();

A3_DA_context := nil;

Plan_5.beginRagged(A3_DA_context, -1,iy+1-(-1));

for __c0 :=  -1 to iy do
begin
  Plan_c0 := AdtArrayPlan.create();
  Plan_c0_context := nil;
  
  Plan_c0.beginRagged(Plan_c0_context,1,1 + ix + 1 -(1));
  
  for __c1 := 1 to 1 + ix do
  begin
    Plan_c1 := AdtArrayPlan.create(1,A2_IA[__c1][__c0] + A2_IB[__c0][__c1] + 1 -(1));
    
    Plan_c0.addArrayPlan(Plan_c1, __c1);
    
    Plan_c1.destroy();
  end;
  
  Plan_c0.endRagged();
  Plan_5.addArrayPlan(A3_DA_context, Plan_c0, __c0);
  
  Plan_c0.destroy();
end;

Plan_5.endRagged(A3_DA_context);

Plan_5.create(_MemAllocator, A3_DA);

zero(A3_DA);

Plan_6 := AdtArrayPlan.create();

A3_DB_context := nil;

Plan_6.beginRagged(A3_DB_context, -1,iy+1-(-1));

for __c0 :=  -1 to iy do
begin
  Plan_c0 := AdtArrayPlan.create();
  Plan_c0_context := nil;
  
  Plan_c0.beginRagged(Plan_c0_context,1,1 + ix + 1 -(1));
  
  for __c1 := 1 to 1 + ix do
  begin
    Plan_c1 := AdtArrayPlan.create(1,A2_IA[__c1][__c0] + 1 -(1));
    
    Plan_c0.addArrayPlan(Plan_c1, __c1);
    
    Plan_c1.destroy();
  end;
  
  Plan_c0.endRagged();
  Plan_6.addArrayPlan(A3_DB_context, Plan_c0, __c0);
  
  Plan_c0.destroy();
end;

Plan_6.endRagged(A3_DB_context);

Plan_6.create(_MemAllocator, A3_DB);

zero(A3_DB);

Plan_7 := AdtArrayPlan.create();
Plan_7.initialise(-1,iy+1-(-1));

A3_DC_context := nil;

Plan_7.beginRagged(A3_DC_context, 1,1+ix+1-(1));

for __c0 := 1 to 1 + ix do
begin
  Plan_c0 := AdtArrayPlan.create(1,A1_I[__c0] + 1 -(1));
  
  Plan_7.addArrayPlan(A3_DC_context, Plan_c0, __c0);
  
  Plan_c0.destroy();
end;

Plan_7.endRagged(A3_DC_context);

Plan_7.create(_MemAllocator, A3_DC);

zero(A3_DC);

Plan_8 := AdtArrayPlan.create();

A3_DD_context := nil;

Plan_8.beginRagged(A3_DD_context, 1,1+ix+1-(1));

for __c0 := 1 to 1 + ix do
begin
  Plan_c0 := AdtArrayPlan.create();
  Plan_c0_context := nil;
  
  Plan_c0.beginRagged(Plan_c0_context, -1,iy + 1 -( -1));
  
  for __c1 :=  -1 to iy do
  begin
    Plan_c1 := AdtArrayPlan.create(1,A1_I[__c0] + 1 -(1));
    
    Plan_c0.addArrayPlan(Plan_c1, __c1);
    
    Plan_c1.destroy();
  end;
  
  Plan_c0.endRagged();
  Plan_8.addArrayPlan(A3_DD_context, Plan_c0, __c0);
  
  Plan_c0.destroy();
end;

Plan_8.endRagged(A3_DD_context);

Plan_8.create(_MemAllocator, A3_DD);

zero(A3_DD);

