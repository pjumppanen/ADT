procedure AdtArrays.mulby(pArray : <T>; value : <D>) ; overload;

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
    pData[cn] := pData[cn] * value;
  end;
end;

procedure AdtArrays.divby(pArray : <T>; value : <D>) ; overload;

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
    pData[cn] := pData[cn] / value;
  end;
end;
