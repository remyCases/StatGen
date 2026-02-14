subroutine compute_array_fortran(arr, n, total)
    implicit none
    integer, intent(in) :: n
    real, intent(in) :: arr(n)
    real, intent(inout) :: total
    integer :: i

    do i = 1, n
        total = total + arr(i) * 2
    end do

    print '("COMPUTE IN FORTRAN = ", F8.2)', total
end subroutine compute_array_fortran

subroutine sum_matrixes(a, b, sum, n)
    implicit none
    integer, intent(in) :: n, a(n, n), b(n, n)
    integer, intent(inout) :: sum(n, n)
    integer :: i, j

    do 20 j = 1, n
        do 10 i = 1, n
            sum(j, i) = a(j, i) + b(j, i)
10      continue
20  continue

end subroutine sum_matrixes
