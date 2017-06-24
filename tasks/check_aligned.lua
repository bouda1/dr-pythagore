function dump(o, indent)
    local tab
    if not indent then
        indent = 0
        tab = ''
    else
        tab = string.rep(' ', indent)
    end
    if type(o) == 'table' then
        local s = '{\n'
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = "'"..k.."'" end
            s = s..tab..'  ['..k..'] = '..dump(v, indent + 2)..',\n'
        end
        return s..tab..'}'
    else
        return tostring(o)
    end
end

function routine()
    local aligned = Plane:getRelations('Aligned');
    local notaligned = Plane:getRelations('NotAligned');
    for j,w in ipairs(notaligned) do
        for i,v in ipairs(aligned) do
            local vv = v.sort()
            print(dump(v))
        end
    end
end

