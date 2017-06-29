function Equals(a, b)
    local distinct = Plane:getRelations('Distinct')
    for i,v in ipairs(distinct) do
        if (a == v[1] and b == v[2]) or (a == v[2] and b == v[1]) then
            return false, 'ERROR: '..a..' and '..b..' cannot be equal and distinct at the same time.'
        end
    end
    print(a..' and '..b..' are equal.')
    return true
end
