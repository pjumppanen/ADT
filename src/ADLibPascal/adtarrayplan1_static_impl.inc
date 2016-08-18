  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1B; const pRefArray : ARRAY_1B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2B; const pRefArray : ARRAY_2B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3B; const pRefArray : ARRAY_3B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4B; const pRefArray : ARRAY_4B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5B; const pRefArray : ARRAY_5B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6B; const pRefArray : ARRAY_6B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7B; const pRefArray : ARRAY_7B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8B; const pRefArray : ARRAY_8B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9B; const pRefArray : ARRAY_9B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10B; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10B(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10B; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10B(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10B; const pRefArray : ARRAY_10B) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10B(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10B) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1C; const pRefArray : ARRAY_1C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2C; const pRefArray : ARRAY_2C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3C; const pRefArray : ARRAY_3C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4C; const pRefArray : ARRAY_4C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5C; const pRefArray : ARRAY_5C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6C; const pRefArray : ARRAY_6C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7C; const pRefArray : ARRAY_7C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8C; const pRefArray : ARRAY_8C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9C; const pRefArray : ARRAY_9C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10C; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10C(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10C; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10C(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10C; const pRefArray : ARRAY_10C) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10C(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10C) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UC; const pRefArray : ARRAY_1UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UC; const pRefArray : ARRAY_2UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UC; const pRefArray : ARRAY_3UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UC; const pRefArray : ARRAY_4UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UC; const pRefArray : ARRAY_5UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UC; const pRefArray : ARRAY_6UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UC; const pRefArray : ARRAY_7UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UC; const pRefArray : ARRAY_8UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UC; const pRefArray : ARRAY_9UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10UC; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10UC(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UC; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10UC(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UC; const pRefArray : ARRAY_10UC) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10UC(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UC) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1I; const pRefArray : ARRAY_1I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2I; const pRefArray : ARRAY_2I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3I; const pRefArray : ARRAY_3I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4I; const pRefArray : ARRAY_4I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5I; const pRefArray : ARRAY_5I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6I; const pRefArray : ARRAY_6I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7I; const pRefArray : ARRAY_7I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8I; const pRefArray : ARRAY_8I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9I; const pRefArray : ARRAY_9I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10I; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10I(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10I; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10I(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10I; const pRefArray : ARRAY_10I) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10I(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10I) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1S; const pRefArray : ARRAY_1S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2S; const pRefArray : ARRAY_2S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3S; const pRefArray : ARRAY_3S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4S; const pRefArray : ARRAY_4S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5S; const pRefArray : ARRAY_5S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6S; const pRefArray : ARRAY_6S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7S; const pRefArray : ARRAY_7S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8S; const pRefArray : ARRAY_8S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9S; const pRefArray : ARRAY_9S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10S; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10S(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10S; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10S(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10S; const pRefArray : ARRAY_10S) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10S(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10S) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1US; const pRefArray : ARRAY_1US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2US; const pRefArray : ARRAY_2US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3US; const pRefArray : ARRAY_3US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4US; const pRefArray : ARRAY_4US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5US; const pRefArray : ARRAY_5US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6US; const pRefArray : ARRAY_6US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7US; const pRefArray : ARRAY_7US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8US; const pRefArray : ARRAY_8US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9US; const pRefArray : ARRAY_9US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10US; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10US(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10US; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10US(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10US; const pRefArray : ARRAY_10US) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10US(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10US) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1L; const pRefArray : ARRAY_1L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2L; const pRefArray : ARRAY_2L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3L; const pRefArray : ARRAY_3L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4L; const pRefArray : ARRAY_4L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5L; const pRefArray : ARRAY_5L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6L; const pRefArray : ARRAY_6L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7L; const pRefArray : ARRAY_7L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8L; const pRefArray : ARRAY_8L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9L; const pRefArray : ARRAY_9L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10L; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10L(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10L; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10L(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10L; const pRefArray : ARRAY_10L) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10L(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10L) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UL; const pRefArray : ARRAY_1UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UL; const pRefArray : ARRAY_2UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UL; const pRefArray : ARRAY_3UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UL; const pRefArray : ARRAY_4UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UL; const pRefArray : ARRAY_5UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UL; const pRefArray : ARRAY_6UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UL; const pRefArray : ARRAY_7UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UL; const pRefArray : ARRAY_8UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UL; const pRefArray : ARRAY_9UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10UL; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10UL(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UL; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10UL(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UL; const pRefArray : ARRAY_10UL) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10UL(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10UL) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1F; const pRefArray : ARRAY_1F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2F; const pRefArray : ARRAY_2F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3F; const pRefArray : ARRAY_3F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4F; const pRefArray : ARRAY_4F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5F; const pRefArray : ARRAY_5F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6F; const pRefArray : ARRAY_6F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7F; const pRefArray : ARRAY_7F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8F; const pRefArray : ARRAY_8F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9F; const pRefArray : ARRAY_9F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10F; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10F(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10F; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10F(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10F; const pRefArray : ARRAY_10F) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10F(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10F) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_1D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_1D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_1D; const pRefArray : ARRAY_1D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_1D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_1D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_2D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_2D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_2D; const pRefArray : ARRAY_2D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_2D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_2D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_3D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_3D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_3D; const pRefArray : ARRAY_3D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_3D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_3D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_4D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_4D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_4D; const pRefArray : ARRAY_4D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_4D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_4D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_5D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_5D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_5D; const pRefArray : ARRAY_5D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_5D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_5D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_6D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_6D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_6D; const pRefArray : ARRAY_6D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_6D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_6D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_7D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_7D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_7D; const pRefArray : ARRAY_7D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_7D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_7D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_8D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_8D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_8D; const pRefArray : ARRAY_8D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_8D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_8D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_9D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_9D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_9D; const pRefArray : ARRAY_9D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_9D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_9D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
  //  ----------------------------------------------------------------------------
  // existing array query method - use to obtain an array from a pointer
  // passed from R that has previously been mapped by this array plan
  function AdtArrayPlan.existing(var pArray : ARRAY_10D; pExisting : pchar) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10D(Actor.existing(varType(pArray), pExisting))
    else
      pArray := nil;

    existing := (pArray <> nil);
  end;

  // New array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10D; pExisting : pchar = nil) : boolean ; overload;

  begin
    if (Actor <> nil) then
      pArray := ARRAY_10D(Actor.create(rAllocator, varType(pArray), pExisting))
    else
      pArray := nil;

    create := (pArray <> nil);
  end;

  // Same shape array creation method
  function AdtArrayPlan.create(rAllocator : AdtMemAllocator; var pArray : ARRAY_10D; const pRefArray : ARRAY_10D) : boolean ; static ; overload;

  begin
    pArray := ARRAY_10D(AdtArrayPlanActor.createSameShape(rAllocator, pchar(pRefArray)));

    create := (pArray <> nil);
  end;

  // array destruction method
  procedure AdtArrayPlan.destroy(rAllocator : AdtMemAllocator; var pArray : ARRAY_10D) ; static ; overload;

  begin
    AdtArrayPlanActor.destroy(rAllocator, pchar(pArray));
  end;
