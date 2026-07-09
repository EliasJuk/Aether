-- abilities/fireball.lua
function on_cast(player, target)
    deal_damage(target, 50)
    spawn_effect("fire", target.x, target.y, target.z)
end