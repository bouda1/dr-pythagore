function NotAligned(a, b, c)
    local aligned = Plane:getRelations('Aligned')
    for i,v in ipairs(aligned) do
        if a == v[1] then
            if (b == v[2] and c == v[3])
                or (b == v[3] and c == v[2]) then
                return false, 'ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.'
            end
        elseif a == v[2] then
            if (b == v[1] and c == v[3]) or (b == v[3] and c == v[1]) then
                return false, 'ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.'
            end
        elseif a == v[3] then
            if (b == v[1] and c == v[2]) or (b == v[2] and c == v[1]) then
                return false, 'ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.'
            end
        end
    end
    print(a..', '..b..', '..c..' are well not aligned.')

    Plane:setPointRelation('Distinct', a, b)
    Plane:setPointRelation('Distinct', a, c)
    Plane:setPointRelation('Distinct', b, c)
    return true
end
