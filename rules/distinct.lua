function Distinct(a, b)
    local equals = Plane:getRelations('Equals')
    for i,v in ipairs(equals) do
        if (a == v[1] and b == v[2]) or (a == v[2] and b == v[1]) then
            return false, 'ERROR: '..a..' and '..b..' cannot be equal and distinct at the same time.'
        end
    end
    print(a..' and '..b..' are distinct.')
    return true
end
