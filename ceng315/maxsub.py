def maxsubcrossingmid(lst, low, high):
    mid = (low + high) / 2
    left_sum = 0
    sum = 0
    i = mid
    i_idx = i

    while i >= low:
        sum += lst[i]
        if sum > left_sum:
            left_sum = sum
            i_idx = i
        i -= 1

    right_sum = 0
    sum = 0
    j = mid + 1
    j_idx = j

    while j <= high:
        sum += lst[j]
        if sum > right_sum:
            right_sum = sum
            j_idx = j
        j += 1

    return (i_idx, j_idx, left_sum+right_sum)


def maxsub(lst, low, high):
    if low == high:
        return (low, high, lst[low])
    mid = (low + high) / 2

    left_sub = maxsub(lst, low, mid)
    right_sub = maxsub(lst, mid+1, high)
    sub_crossing_mid = maxsubcrossingmid(lst, low, high)

    if left_sub[2] > right_sub[2] and left_sub[2] > sub_crossing_mid[2]:
        return left_sub
    elif right_sub[2] > left_sub[2] and right_sub[2] > sub_crossing_mid[2]:
        return right_sub
    else:
        return sub_crossing_mid

l = [-1] * 9

print maxsub(l, 0, len(l)-1)
