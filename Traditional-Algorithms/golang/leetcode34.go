func searchRange(nums []int, target int) []int {
    length := len(nums)
    if length == 0{
        return []int{-1, -1}
    }
    first := findFirstElem(nums, target)
    end := findLastElem(nums, target)
    result := []int{first, end}
    return result
}

func findFirstElem(nums []int, target int) int{
    length := len(nums)
    left := 0
    right := length -1
    for;left < right;{
        mid := left + (right - left) / 2
        if nums[mid] < target{
            left = mid + 1
        }else{
            right = mid
        }
    }
    if nums[left] == target{
        return left
    }
    return -1
}

func findLastElem(nums []int, target int) int{
    length := len(nums)
    left := 0
    right := length - 1
    for;left < right;{
        mid := left + (right - left + 1)/2
        if nums[mid] > target{
            right = mid -1
        }else{
            left = mid
        }
    }
    if nums[left] == target{
        return left
    }
    return -1
}