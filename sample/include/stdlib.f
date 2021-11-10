! ----------------------------------------------------------------------------
! Standard definitions of needed functions
! ----------------------------------------------------------------------------
SUBROUTINE CheckSizeInteger1(a,i)
    INTEGER(1) :: i
    INTEGER(1) :: a(:)
END

! ----------------------------------------------------------------------------

SUBROUTINE CheckSizeInteger4(a,i)
    INTEGER(4) :: i
    INTEGER(4) :: a(:)
END

! ----------------------------------------------------------------------------

SUBROUTINE CheckSizeInteger8(a,i)
    INTEGER(8) :: i
    INTEGER(8) :: a(:)
END

! ----------------------------------------------------------------------------

SUBROUTINE CheckSizeReal4(a,i)
    INTEGER(4) :: i
    REAL(4) :: a(:)
END

! ----------------------------------------------------------------------------

SUBROUTINE CheckSizeReal8(a,i)
    INTEGER(4) :: i
    REAL(8) :: a(:)
END

! ----------------------------------------------------------------------------

SUBROUTINE CheckSizeReal16(a,i)
    INTEGER(4) :: i
    REAL(16) :: a(:)
END

! ----------------------------------------------------------------------------

INTEGER(4) FUNCTION one_if(a)
    LOGICAL :: a
    IF (A) THEN
        one_if = 1
    ELSE
        one_if = 0
    END IF
END
