procedure zero(var rArrayOriginValue : <T>; nCount : longint) ; overload;

begin
  FillChar(rArrayOriginValue, nCount * SizeOf(rArrayOriginValue), 0);
end;

procedure xcopy(var rSrcArrayOriginValue : <T>; var rDestArrayOriginValue : <T>; nCount : longint) ; overload;

begin
  Move(rSrcArrayOriginValue, rDestArrayOriginValue, nCount * SizeOf(rSrcArrayOriginValue));
end;

