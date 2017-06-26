function Aligned(a, b, c)
    local notaligned = Plane:getRelations('NotAligned')
    for i,v in ipairs(notaligned) do
        if a == v[1] then
            if (b == v[2] and c == v[3])
                or (b == v[3] and c == v[2]) then
                print('ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.')
                return
            end
        elseif a == v[2] then
            if (b == v[1] and c == v[3]) or (b == v[3] and c == v[1]) then
                print('ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.')
                return
            end
        elseif a == v[3] then
            if (b == v[1] and c == v[2]) or (b == v[2] and c == v[1]) then
                print('ERROR: '..a..', '..b..' and '..c..' cannot be aligned and not aligned at the same time.')
                return
            end
        end
    end
    print(a..', '..b..', '..c..' are well aligned.')
end
