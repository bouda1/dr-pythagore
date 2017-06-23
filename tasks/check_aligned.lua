function routine()
    local elts = Plane:getRelations('Aligned');
    for i,v in ipairs(elts) do
        print('  '..i..' -> '..v)
    end
end

