-- --------------------------------------------------
-- pw.lua - the game's logic
-- okertanov@gmail.com (c) 2010
-- --------------------------------------------------

require 'oop'

local settings =
{
    name='AI-Contest Strategy'
};

-- --------------------------------------------------
-- Game Logic
-- --------------------------------------------------
UNKNOWN = -1;
NEUTRAL = 0;
MINE    = 1;
ENEMY   = 2;

F_ALL     = UNKNOWN;
F_MY      = MINE;
F_NEUTRAL = NEUTRAL;
F_ENEMY   = ENEMY;
F_NOTMY   = (NEUTRAL + ENEMY) * UNKNOWN;

GO = "go";
ENDGO = "end";
ENDL = "\n";

function dtrace(fmt, ...)
    io.stderr:write(fmt:format(...), "\n");
end

GameLogic = {}; -- Forward Declaration
Class (GameLogic);

function GameLogic:Initialize() -- Constructor
    dtrace('GameLogic:Initialize...');
end

function GameLogic:Release() -- Destructor
    dtrace('GameLogic:Release...');
end

function GameLogic:Tokenize(str, delims)
    local tokens = {};
    local sep = delims or " ";
    local pattern = string.format("([^%s]+)", sep)

    for t in string.gmatch( str, pattern ) do
        tokens[#tokens+1] = t;
    end

    return tokens;
end

function GameLogic:CheckOrderRestrictions()
end

function GameLogic:CheckWinConditions()
end

function GameLogic:IoRead()
    local buf = io.read();
    return buf;
end

function GameLogic:IoWrite(buf)
    io.write(buf);
    io.flush();
end

function GameLogic:Play()
    local line = "";
    local map_data = "";

    while true do
        line = self:IoRead();
        line = string.gsub(line, "#.*", ""); --strip comment
        if (line == GO) then
            pw = PlanetWars:new();
            pw:Initialize(map_data);
            pw:DoTurn();
            pw:FinishTurn();
            map_data = "";
        elseif (line == ENDGO) then
            return 0;
        else
            map_data = map_data..line..ENDL;
        end
    end
end

function GameLogic:Run(map_file, robots_list)
    -- TODO:
end

function GameLogic:VisualizeTurn()
    -- TODO:
end

function GameLogic:VisualizeGame()
    -- TODO:
end

-- --------------------------------------------------
-- Fleet
-- --------------------------------------------------
Fleet = {}; -- Forward Declaration
Class(Fleet);

function Fleet:Initialize(  owner,
                            num_ships,
                            src_panet,
                            dst_planet,
                            total_trip_length,
                            turns_remaining  ) -- Constructor
    -- Members
    self.owner = tonumber(owner) or -1;
    self.num_ships = tonumber(num_ships) or 0;
    self.src_panet = tonumber(src_panet) or -1;
    self.dst_planet = tonumber(dst_planet) or -1;
    self.total_trip_length = tonumber(total_trip_length) or -1;
    self.turns_remaining = tonumber(turns_remaining) or -1;
end

function Fleet:Release() -- Destructor
end

function Fleet:Owner()
    return self.owner;
end

function Fleet:NumShips()
    return self.num_ships;
end

function Fleet:SourcePlanet()
    return self.src_panet;
end

function Fleet:DestinationPlanet()
    return self.dst_planet;
end

function Fleet:TotalTripLength()
    return self.total_trip_length;
end

function Fleet:TurnsRemaining()
    return self.turns_remaining;
end

-- --------------------------------------------------
-- Planet
-- --------------------------------------------------
Planet = {}; -- Forward Declaration
Class(Planet);

function Planet:Initialize( id,
                            owner,
                            num_ships,
                            growth_rate,
                            x,
                            y  ) -- Constructor
    -- Members
    self.id = tonumber(id) or -1;
    self.owner = tonumber(owner) or -1;
    self.num_ships = tonumber(num_ships) or 0;
    self.growth_rate = tonumber(growth_rate) or 0;
    self.position = {};
    self.position.x = tonumber(x) or -1;
    self.position.y = tonumber(y) or -1;
end

function Planet:Release() -- Destructor
end

function Planet:PlanetId()
    return self.id;
end

function Planet:Owner(nowner)
    if ( nowner ~= nil ) then self.owner = tonumber(nowner) end

    return self.owner;
end

function Planet:NumShips(ns)
    if ( ns ~= nil ) then self.num_ships = tonumber(ns) end

    return self.num_ships;
end

function Planet:GrowthRate()
    return self.growth_rate;
end

function Planet:Position()
    return {x=self.position.x, y=self.position.y};
end

function Planet:AddShips(amount)
    self.num_ships = tonumber(self.num_ships + amount);
end

function Planet:RemoveShips(amount)
    self.num_ships = tonumber(self.num_ships - amount);
end

-- --------------------------------------------------
-- PlanetWars
-- --------------------------------------------------
PlanetWars = {}; -- Forward Declaration
Class(PlanetWars);

function PlanetWars:Initialize(game_state) -- Constructor
    -- Members
    self.game_state = game_state;
    self.planets = {};
    self.fleets  = {};

    self:ParseGameState(self.game_state);
end

function PlanetWars:Release() -- Destructor
    self.planets = {};
    self.fleets  = {};
end

function PlanetWars:NumPlanets()
    return #self.planets;
end

function PlanetWars:GetPlanet(planet_id)
    local idx = tonumber(planet_id + 1);
    return self.planets[idx];
end

function PlanetWars:NumFleets()
    return #self.fleets;
end

function PlanetWars:GetFleet(fleet_id)
    local idx = tonumber(fleet_id + 1);
    return self.fleets[idx];
end

function PlanetWars:Planets(filter)
    -- ALL, MY, NEUTRAL, ENEMY, NOTMY
    local filtered_planets = {};

    for k,v in ipairs (self.planets) do
        if      ( filter == F_ALL ) then
            table.insert(filtered_planets, v);
        elseif ( filter == F_MY ) then
            if ( v:Owner() == MINE  ) then
                table.insert(filtered_planets, v);
            end
        elseif ( filter == F_NEUTRAL ) then
            if ( v:Owner() == NEUTRAL ) then
                table.insert(filtered_planets, v);
            end
        elseif ( filter == F_ENEMY ) then
            if ( v:Owner() > MINE ) then
                table.insert(filtered_planets, v);
            end
        elseif ( filter == F_NOTMY ) then
            if ( v:Owner() ~= MINE ) then
                table.insert(filtered_planets, v);
            end
        end
    end

    return filtered_planets;
end

function PlanetWars:Fleets(filter)
    -- ALL, MY, ENEMY
    local filtered_fleets = {};

    for k,v in ipairs (self.fleets) do
        if      ( filter == F_ALL ) then
            table.insert(filtered_fleets, v);
        elseif ( filter == F_MY ) then
            if ( v:Owner() == MINE  ) then
                table.insert(filtered_fleets, v);
            end
        elseif ( filter == F_ENEMY ) then
            if ( v:Owner() > MINE ) then
                table.insert(filtered_fleets, v);
            end
        end
    end

    return filtered_fleets;
end

function PlanetWars:ToString()
    local pwstr = '';

    for k,v in ipairs (self.planets) do
        pwstr = pwstr.."P "..v:Position().x.." "..v:Position().y.." "..v:Owner()..
        " "..v:NumShips().." "..v:GrowthRate()..ENDL;
    end

    for k,v in ipairs (self.fleets) do
        pwstr = pwstr.."F "..v:Owner().." "..v:NumShips().." "..
        v:SourcePlanet().." "..f:DestinationPlanet().." "..
        v:TotalTripLength().." "..v:TurnsRemaining()..ENDL;
    end

    return pwstr;
end

function PlanetWars:Distance(src_planet, dst_planet)
    local source = self:GetPlanet(src_planet);
    local destination = self:GetPlanet(dst_planet);

    if ( not source or not destination ) then return -1; end

    local dx = source:Position().x - destination:Position().x;
    local dy = source:Position().y - destination:Position().y;
    local distance = math.ceil( math.sqrt(dx * dx + dy * dy) );

    return distance;
end

function PlanetWars:IssueOrder(  src_planet,
                                 dst_planet,
                                 num_ships  )
    local nships = math.floor(num_ships);
    local order = src_planet.." "..dst_planet.." "..nships;

    GameLogic:IoWrite(order..ENDL);
end

function PlanetWars:IsAlive(player_id)
    local is_alive = false;

    for k,v in ipairs (self.planets) do
        if (v:Owner() == player_id) then
            is_alive = true;
        end
    end

    for k,v in ipairs (self.fleets) do
        if (v:Owner() == player_id) then
            is_alive = true;
        end
    end

    return is_alive;
end

function PlanetWars:NumShips(filter)
    local num_ships = 0;

    local planets = self:Planets(filter);
    local fleets = self:Fleets(filter);

    for k,v in ipairs (planets) do
            num_ships = tonumber(num_ships + v:NumShips());
    end

    for k,v in ipairs (fleets) do
            num_ships = tonumber(num_ships + v:NumShips());
    end

    return num_ships;
end

function PlanetWars:FinishTurn()
    GameLogic:IoWrite(GO..ENDL);
end

function PlanetWars:ParseGameState(game_state)
    self.planets = {};
    self.fleets = {};

    local lines = GameLogic:Tokenize(game_state, ENDL);
    local planet_id = 0;

    for k,v in ipairs (lines) do
        local line = v;
        line = string.gsub(line, "#.*", "");

        local tokens = GameLogic:Tokenize(line, " ");
        if ( #tokens ) then
            if (tokens[1] == "P") then
                if (#tokens ~= 6) then return false; end
                local planet = Planet:new();
                planet:Initialize(  --[[id]]planet_id,
                                    --[[owner]]tokens[4],
                                    --[[num ships]]tokens[5],
                                    --[[growth]]tokens[6],
                                    --[[x]]tokens[2],
                                    --[[y]]tokens[3]  );
                table.insert(self.planets, planet);
                planet_id = planet_id + 1;
            elseif (tokens[1] == "F") then
                if (#tokens ~= 7) then return false; end
                local fleet = Fleet:new();
                fleet:Initialize(  --[[owner]]tokens[2],
                                   --[[num ships]]tokens[3],
                                   --[[src]]tokens[4],
                                   --[[dst]]tokens[5],
                                   --[[length]]tokens[6],
                                   --[[remaining]]tokens[7]  );
                table.insert(self.fleets, fleet);
            else
                return false;
            end
        end
    end

    return true;
end

function PlanetWars:IsPlanetInSrc(table, planet_id)
    for k, v in pairs(table) do
        if(v.tsrc == planet_id) then return true end
    end

    return false;
end

function PlanetWars:IsPlanetInFight(table, planet_id)
    for k, v in pairs(table) do
        if(v:SourcePlanet() == planet_id) then return true end
    end

    return false;
end

function PlanetWars:IsPlanetInAttackFrom(table, src_planet_id, dst_planet_id)
    for k, v in pairs(table) do
        if(v:SourcePlanet() == src_planet_id and v:DestinationPlanet() == dst_planet_id) then return true end
    end

    return false;
end

function PlanetWars:IsPlanetInDst(table, planet_id)
    for k, v in pairs(table) do
        if(v.tdst == planet_id) then return true end
    end

    return false;
end

function PlanetWars:GenerateOrders(turns)
    for k,v in ipairs (turns) do
        self:IssueOrder(v.tsrc, v.tdst, v.tships);
    end
end

function PlanetWars:AddOrder(t, turn)
    table.insert(t, turn);
end

global_turn_count = 0;
strategy = 'nearestweak'; -- weakest, nearest, nearestweak, agressor

function PlanetWars:DoTurn()
    local turn_loop = true;
    local turns = {};
    local turn_count = 0;

    global_turn_count = global_turn_count + 1;

    if ( (self:NumShips(F_MY) - self:NumShips(F_ENEMY)) > 0 ) then strategy = 'agressor'; end
    dtrace('DoTurn(%d - %s): Turning... with all ships = %d, my = %d, enemy = %d', global_turn_count, strategy, self:NumShips(F_ALL), self:NumShips(F_MY), self:NumShips(F_ENEMY));

    while (turn_loop) do
        turn_count = turn_count + 1;

        -- Find my strongest planet.
        local src = -1;
        local src_score = -999999.0;
        local src_num_ships = 0;
        local my_planets = self:Planets(F_MY);
        local src_planet = nil;
        for k,v in ipairs (my_planets) do
            if (    (not self:IsPlanetInSrc(turns, v:PlanetId())) --[[  and
                    (not PlanetWars:IsPlanetInFight(self:Fleets(F_MY), v:PlanetId()) )  ]]
               ) then
                local score = v:NumShips() / (1 + v:GrowthRate());
                if (score > src_score) then
                    src_score = score;
                    src = v:PlanetId();
                    src_num_ships = v:NumShips();
                    src_planet = v;
                end
            end
        end

        -- Find the target enemy or neutral planet.
        local not_my_planets = nil;
        if ( strategy == 'weakest' ) then not_my_planets = self:Planets(F_NOTMY);
        elseif ( strategy == 'nearest' or strategy == 'nearestweak' ) then not_my_planets = self:Planets(F_NOTMY);
        elseif ( strategy == 'agressor' ) then not_my_planets = self:Planets(F_ENEMY);
        else not_my_planets = self:Planets(F_NOTMY); end

        dtrace('DoTurn(%d - %s): Iterating... %d', global_turn_count, strategy, #not_my_planets);

        local dst = -1;
        local dst_score = -999999.0;
        local dst_distance = 999999.0;
        local dst_num_ships = 0;
        local dst_growth = 0;
        local dst_planet = nil;
        local dst_near_weak_planet = nil;
        if ( src >= 0 ) then
            for k,v in ipairs (not_my_planets) do
                if (
                        (not self:IsPlanetInDst(turns, v:PlanetId())) and
                        (not self:IsPlanetInAttackFrom(self:Fleets(F_MY), src_planet:PlanetId(), v:PlanetId()))
                   ) then
                    if ( strategy == 'weakest' ) then
                        local score = (1 + v:GrowthRate()) / v:NumShips(); -- v:NumShips();
                        if (score > dst_score) then
                            dst_score = score;
                            dst = v:PlanetId();
                            dst_num_ships = v:NumShips();
                            dst_planet = v;
                        end
                    elseif ( strategy == 'nearest' ) then
                        local distance = self:Distance(src, v:PlanetId());
                        if ( distance > 0 and distance < dst_distance ) then
                            dst_distance = distance;
                            dst = v:PlanetId();
                            dst_num_ships = v:NumShips();
                            dst_planet = v;
                        end
                    elseif ( strategy == 'nearestweak' or strategy == 'agressor' ) then
                        local score = (1 + v:GrowthRate()) / v:NumShips(); -- v:NumShips();
                        local distance = self:Distance(src, v:PlanetId());
                        if (score > dst_score) then
                            dst_score = score;
                            dst = v:PlanetId();
                            dst_num_ships = v:NumShips();
                            dst_planet = v;
                            if ( distance > 0 and distance < dst_distance ) then
                                dst_distance = distance;
                                dst_neqr_weak_planet = dst_planet;
                            end
                        end
                        if (dst_near_weak_planet) then
                            dst = dst_near_weak_planet:PlanetId();
                            dst_num_ships = dst_near_weak_planet:NumShips();
                            dst_planet = dst_near_weak_planet;
                        end
                    end
                end
            end -- for
        end

        -- Add the turn
        if ( src >= 0 and dst >= 0 ) then
            -- Normalize dst_num_ships
            -- dst_num_ships = dst_num_ships + dst_planet:GrowthRate();

            -- Prepare the Fleet with proper ships number
            local ships = -1;
            if ( strategy == 'weakest' ) then
                if (src_num_ships >= dst_num_ships) then
                    ships = math.floor( (dst_num_ships + ((src_num_ships - dst_num_ships) / 4)) );
                    strategy = 'nearestweak';
                else
                    -- ships = math.floor( src_num_ships / 2 );
                    -- dtrace('DoTurn(%d - %s): No Power to fight from %d(%d) against %d(%d), sending only a half (%d)', global_turn_count, strategy, src, src_num_ships, dst, dst_num_ships, ships);
                    dtrace('DoTurn(%d - %s): No Power to fight from %d(%d) against %d(%d)', global_turn_count, strategy, src, src_num_ships, dst, dst_num_ships);
                end
            elseif ( strategy == 'nearest' or strategy == 'nearestweak' or strategy == 'agressor' ) then
                if (src_num_ships >= dst_num_ships) then
                    ships = math.floor( (dst_num_ships + ((src_num_ships - dst_num_ships) / 4)) );
                else
                    -- ships = math.floor( src_num_ships / 2 );
                    -- dtrace('DoTurn(%d - %s): No Power to fight from %d(%d) against %d(%d), sending only a half (%d)', global_turn_count, strategy, src, src_num_ships, dst, dst_num_ships, ships);
                    dtrace('DoTurn(%d - %s): No Power to fight from %d(%d) against %d(%d)', global_turn_count, strategy, src, src_num_ships, dst, dst_num_ships);

                    -- if ( strategy == 'agressor') then
                        ships = math.floor( src_num_ships - 1 ); -- master ships
                        local total_spk_to_send = ships;
                        local candidates = self:Planets(F_MY);
                        dtrace('DoTurn(%d - %s): But we will try to find resources to kombat using %d!', global_turn_count, strategy, #candidates);
                        for k,v in ipairs (candidates) do
                            local spk = v:PlanetId();
                            if ( ( not self:IsPlanetInSrc(turns, spk) ) and
                                 ( spk ~= src )
                                ) then
                                if ( v:NumShips() > 0 ) then
                                    local spk_to_send = math.floor(v:NumShips() - 1);
                                    dtrace('DoTurn(%d - %s): agressive from %d(%d) against %d(%d) with %d ships (%d left)', global_turn_count, strategy,
                                            spk, v:NumShips(), dst, dst_num_ships, spk_to_send, v:NumShips() - spk_to_send);
                                    table.insert(turns, {tsrc=spk, tdst=dst, tships=spk_to_send});
                                    v:RemoveShips(spk_to_send);
                                    total_spk_to_send = total_spk_to_send + spk_to_send;
                                end
                            end

                            if (total_spk_to_send > dst_num_ships) then break; end
                        end
                    -- end
                end
            end

            if ( ships > 0 ) then
                dtrace('DoTurn(%d - %s): from %d(%d) against %d(%d) with %d ships (%d left)', global_turn_count, strategy, src, src_num_ships, dst, dst_num_ships, ships, src_num_ships - ships);
                self:AddOrder(turns, {tsrc=src, tdst=dst, tships=ships});
                src_planet:RemoveShips(ships);
            end
        else
            dtrace('DoTurn(%d - %s): Invalid Turn where from %d to %d', global_turn_count, strategy, src, dst);
        end

        -- EndOfTurn Conditions
        if ( turn_count >= #my_planets ) then turn_loop = false; end
    end --while

    dtrace("DoTurn(%d - %s): Sending orders %d!", global_turn_count, strategy, #turns);
    -- Send the Ships
    self:GenerateOrders(turns);
end
