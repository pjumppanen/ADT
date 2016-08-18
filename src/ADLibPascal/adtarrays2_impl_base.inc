procedure AdtArrays.set_all(pArray : <T>; value : <D>) ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pData       : p<D>;
  nCount      : longint;
  cn          : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := p<D>(firstData(pArrayInfo^));
  nCount      := lengthOfData(pArrayInfo^) div sizeof(<D>);

  for cn := 0 to nCount - 1 do
  begin
    pData[cn] := value;
  end;
end;

procedure AdtArrays.inc(pArray : <T>) ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pData       : p<D>;
  nCount      : longint;
  cn          : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := p<D>(firstData(pArrayInfo^));
  nCount      := lengthOfData(pArrayInfo^) div sizeof(<D>);

  for cn := 0 to nCount - 1 do
  begin
    pData[cn] := pData[cn] + 1;
  end;
end;

procedure AdtArrays.dec(pArray : <T>) ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pData       : p<D>;
  nCount      : longint;
  cn          : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := p<D>(firstData(pArrayInfo^));
  nCount      := lengthOfData(pArrayInfo^) div sizeof(<D>);

  for cn := 0 to nCount - 1 do
  begin
    pData[cn] := pData[cn] - 1;
  end;
end;

procedure AdtArrays.incby(pArray : <T>; value : <D>) ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pData       : p<D>;
  nCount      : longint;
  cn          : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := p<D>(firstData(pArrayInfo^));
  nCount      := lengthOfData(pArrayInfo^) div sizeof(<D>);

  for cn := 0 to nCount - 1 do
  begin
    pData[cn] := pData[cn] + value;
  end;
end;

procedure AdtArrays.decby(pArray : <T>; value : <D>) ; overload;

var
  pArrayInfo  : PAdtArrayInfo;
  pData       : p<D>;
  nCount      : longint;
  cn          : longint;

begin
  pArrayInfo  := AdtArrayPlanActor_arrayInfo(_MemAllocator, pchar(pArray));
  pData       := p<D>(firstData(pArrayInfo^));
  nCount      := lengthOfData(pArrayInfo^) div sizeof(<D>);

  for cn := 0 to nCount - 1 do
  begin
    pData[cn] := pData[cn] - value;
  end;
end;
