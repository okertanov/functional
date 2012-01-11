--
-- okertanov@gmail.com (c) 2010
--

require 'oop'

-- Settings ----------------------------------------------------------------
local settings =
{
    name='Snayka Game',
    media_dir='media/',
    bg_track='media/korobeiniki.mp3',
    menu_font='media/tahoma.ttf',
    head='media/head.png',
    fruit='media/fruit.png',
    num_of_gadgets=10,
    bg_color = { 50, 55, 50 },          -- RGB
    fg_color = { 250, 250, 250, 255 }   -- RGBA
};

-- Globals ----------------------------------------------------------------
local world  = {};
local screen  = {};

-- Objects ----------------------------------------------------------------
World  = {}; -- Forward Declaration
Screen = {}; -- Forward Declaration
Actor  = {}; -- Forward Declaration
Gadget = {}; -- Forward Declaration
Static = {}; -- Forward Declaration

Class(World);
Class(Screen);
Class(Actor);
Class(Gadget);
Class(Static);

--
-- World
--
function World:Initialize(sc)
    self.w = love.physics.newWorld(sc:GetDimension().w*16, sc:GetDimension().h*16);
    self.w:setGravity(0, 0); -- Zero Gravity
    self.w:setMeter(16);
    self.w:setCallbacks(add, persist, rem, result);

    self.statics  = {};
    self.actors   = {};
    self.gadgets  = {};

    self.surface = love.physics.newBody(self.w, 0, 0, 0);
end

function World:GetWorld()
    return self.w;
end

function World:AddActor(ac)
    table.insert( self.actors, ac );
end

function World:GetActorBy(character)
    return self.actors[1];
end


function World:AddGadget(ga)
    table.insert( self.gadgets, ga );
end

function World:RemoveGadget(ga)
    for k,v in ipairs(self.gadgets) do
        if ga == v then
            table.remove(self.gadgets, k);
            v:Destroy();
        end
    end
end

function World:FindGadgetByName(on)
    for k,v in ipairs(self.gadgets) do
        if v.shape:getData() == on then
            print('Found '..on);
            return v;
        end
    end
    print('Not found '..on);
end

function World:AddStatic(st)
    table.insert( self.statics, st );
end

function World:Update(dt)
    self.w:update(dt);
end

function World:SetupWorld()
    local actor = Actor:new();
    actor:Initialize( world:GetWorld(), love.graphics.newImage(settings.head), screen:GetCenter() );
    world:AddActor(actor);

    for i = 1, settings.num_of_gadgets do
        local g = Gadget:new();
        local rnd_x = math.random(16, screen:GetDimension().w-16);
        local rnd_y = math.random(16, screen:GetDimension().h-16);
        g:Initialize( world:GetWorld(), love.graphics.newImage(settings.fruit), {x=rnd_x, y=rnd_y} );
        world:AddGadget(g);
    end

    local s_width  = screen:GetDimension().w;
    local s_height = screen:GetDimension().h;
    screen:Hint('Screen: '..s_width..'x'..s_height);

    local leftWall = Static:new();
    leftWall:Initialize(world:GetWorld(), {x=0, y=0}, {w=2, h=s_height*2});
    local topWall = Static:new();
    topWall:Initialize(world:GetWorld(), {x=0, y=0},  {w=s_width*2, h=2});
    local rightWall = Static:new();
    rightWall:Initialize(world:GetWorld(), {x=s_width/2, y=0},  {w=2, h=s_height*2});
    local bottomWall = Static:new();
    bottomWall:Initialize(world:GetWorld(), {x=0, y=s_height/2},  {w=s_width*2, h=2});

    world:AddStatic(leftWall);
    world:AddStatic(topWall);
    world:AddStatic(rightWall);
    world:AddStatic(bottomWall);

end

function World:Draw()
    for k,v in ipairs(self.statics) do
        v:Draw();
    end

    for k,v in ipairs(self.actors) do
        v:Draw();
    end

    for k,v in ipairs(self.gadgets) do
        v:Draw();
    end
end

--
-- Screen
--
function Screen:Initialize()
    self.w = love.graphics:getWidth();
    self.h = love.graphics:getHeight();
    self.center = { x = self.w / 2, y = self.h / 2 };
    self.mouse  = { x = 0, y = 0 };
    self.hint   = "";
end

function Screen:SetupScene()
    math.randomseed( os.time() );

    self.bg_music = love.audio.newSource(settings.bg_track);
    self.bg_music:setLooping(true);
    self.bg_music:setVolume(0.1);
    self.bg_music:setPitch(1.3);
    love.audio.play(self.bg_music);

    self.menu_font = love.graphics.newFont(settings.menu_font, 14);
    love.graphics.setFont(self.menu_font);

    love.graphics.setBackgroundColor( unpack(settings.bg_color) );
    love.graphics.setColor( unpack(settings.fg_color) );
end

function Screen:GetDimension()
    return {w=self.w, h=self.h};
end

function Screen:GetCenter()
    return self.center;
end

function Screen:GetMousePos()
    return self.mouse;
end

function Screen:Update(dt)
    screen:UpdateMouse(dt);
    screen:UpdateKeyboard(dt);
end

function Screen:UpdateMouse(dt)
    self.mouse.x = love.mouse.getX();
    self.mouse.y = love.mouse.getY();
end

function Screen:UpdateKeyboard(dt)
    local direction = {x=0, y=0};
    local accel = 50;
    if love.keyboard.isDown( 'up' ) then
        direction.y = -(accel);
    end
    if love.keyboard.isDown( 'down' ) then
        direction.y = (accel);
    end
    if love.keyboard.isDown( 'left' ) then
        direction.x = -(accel);
    end
    if love.keyboard.isDown( 'right' ) then
        direction.x = (accel);
    end

    if ( direction.x ~= 0 or direction.y ~= 0 ) then
        world:GetActorBy().body:applyForce( direction.x, direction.y );
    end

    if love.keyboard.isDown( ' ' ) then
        screen:Hint('Space is pressed.');
        world:GetActorBy():SetPosition( screen:GetCenter() );
    end

    if love.keyboard.isDown( 'lalt' ) then
        screen:Hint('Alt is pressed.');
        world:GetActorBy():SetPosition(screen:GetMousePos());
    end

    if love.keyboard.isDown( 'q' ) then
        screen:Hint('Bye!');
        love.event.push('q');
    end
end

function Screen:Hint(t)
    if ( t ) then
        self.hint = t;
    end
    return self.hint;
end

function Screen:Draw()
    love.graphics.print(settings.name, 10, 40);
    love.graphics.print(self:Hint(), 10, 60);
end

--
-- Actor
--
function Actor:Initialize(wrld, image, pos)
    self.image = image;
    self.w = self.image:getWidth();
    self.h = self.image:getHeight();

    self.body  = love.physics.newBody(wrld, pos.x, pos.y, 5, 5);
    self.shape = love.physics.newCircleShape(self.body, 0, 0, 8);
    self.shape:setData('Actor'..math.random(1024, 65535));
end

function Actor:Destroy()
    self.image = nil;
    self.body  = nil;
    self.shape = nil;
end

function Actor:SetPosition(pos)
    self.body:setPosition(pos.x, pos.y);
    self.body:putToSleep();
end

function Actor:Draw(nx, ny)
    love.graphics.draw(self.image, self.body:getX() - self.w / 2, self.body:getY() - self.h / 2);
    love.graphics.circle("line", self.body:getX(), self.body:getY(), self.shape:getRadius());
end

--
-- Gadget
--
function Gadget:Initialize(wrld, image, pos)
    self.image = image;
    self.w = self.image:getWidth();
    self.h = self.image:getHeight();

    self.body  = love.physics.newBody(wrld, pos.x, pos.y, 5, 1);
    self.shape = love.physics.newCircleShape(self.body, 0, 0, 8);
    self.shape:setData('Gadget'..math.random(1024, 65535));
end

function Gadget:Destroy()
    self.image = nil;
    self.body  = nil;
    self.shape = nil;
end

function Gadget:Draw()
    love.graphics.draw(self.image, self.body:getX(), self.body:getY());
end

--
-- Static
--
function Static:Initialize(wrld, pos, dim)
    self.body  = love.physics.newBody(wrld, pos.x, pos.y, 0, 0);
    self.shape = love.physics.newRectangleShape(self.body, pos.x, pos.y, dim.w, dim.h);
    self.shape:setData("Static-"..pos.x..'x'..pos.y..':'..dim.w..'x'..dim.h..':'..math.random(1024, 65535));
end

function Static:Draw()
    love.graphics.polygon("fill", self.shape:getPoints());
end

-- Love Callbacks ----------------------------------------------------------------
function love.load()
    screen = Screen:new();
    screen:Initialize();
    screen:SetupScene();

    world = World:new();
    world:Initialize(screen);
    world:SetupWorld();
end

function love.draw()
    world:Draw();
    screen:Draw();
end

function love.update(dt)
    world:Update(dt);
    screen:Update(dt);
end

function love.mousepressed(x, y, button)
   if button == 'l' then
      screen.hint = "Mouse button left is pressed at X:"..screen.mouse.x.." Y: "..screen.mouse.y;
   end
end

function add(a, b, coll)
    local text = a.." collding with "..b.." at an angle of "..coll:getNormal().."\n";
end

function persist(a, b, coll)
    local text = a.." touching "..b.."\n";
    screen:Hint(text);
    world:RemoveGadget(world:FindGadgetByName(b));
end

function rem(a, b, coll)
    local text = a.." uncolliding "..b.."\n";
end

function result(a, b, coll)
    local text = a.." hit "..b.."resulting with "..coll:getNormal().."\n";
end

