#pragma once

#ifdef TEST

class BlueCubeScript : public Script
{
    void Start() override
    {
        std::cout << "Blue entity start!" << std::endl;
        
    }

    void Update() override
    {
        
    }

    void OnCollision(Entity entity) override
    {
        if (!entity.IsValid() || static_cast<int>(entity.GetHandler()) == 1) return;
        std::cout << entity.Get<Tag>().name << std::endl;
        //DestroyEntity(entity);
        DestroyEntity(entity);
    }
};

class Game final : public Application
{
    Entity entityA;
    Entity entityB;
    float move = 10;
    float torque = 5;
    
    float time = 0;
    float maxTime = 3;

    Entity entityD;
    
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Test - Alejandro :D");
        {
            entityD = scene.CreateEntity();
            entityD.Add<Physicbody2D>();
            entityD.Add<BoxCollider2D>();
        }
        
        entityA = scene.CreateEntity("Red Cube");
        {
            entityA.Get<Transform>().position += Vector3::up * 2.f;
            entityA.Add<SpriteRenderer>().color = Color::LightRed;
            auto& collider = entityA.Add<BoxCollider2D>();
            entityA.Add<Physicbody2D>().gravityScale = 0;
        }

        entityB = scene.CreateEntity("Ground");
        {
            entityB.Get<Transform>().position += Vector3::down * 2.f;

            auto& collider = entityB.Add<BoxCollider2D>();
            TransformSystem::Rotate(entityB.Get<Transform>(), 12, { 0, 0, 1 });
            collider.center = { 0, 1 };
            collider.size = { 6, 1 };

            auto& pb = entityB.Add<Physicbody2D>();

            pb.bodyType = Physicbody2D::BodyType::Kinematic;
            //pb.RuntimeBody().SetType(b2BodyType::b2_kinematicBody);
        }

        Entity entityC = scene.CreateEntity("Blue Cube");
        {
            entityC.Add<SpriteRenderer>().color = Color::LightBlue;
            entityC.Get<Transform>().position += Vector3::up;
            auto& collider = entityC.Add<BoxCollider2D>();
            entityC.Add<Physicbody2D>();
            entityC.Add<Logic>().AddScript<BlueCubeScript>();
        }

        Entity entityD = scene.CreateEntity("Yellow Circle");
        {
            entityD.Add<CircleRenderer>().color = Color::Yellow;
            entityD.Get<Transform>().position += Vector3::up * 3;
            entityD.Get<Transform>().position += Vector3::right;
            auto& collider = entityD.Add<CircleCollider>();
            collider.radius /= 2;
            entityD.Add<Physicbody2D>();
        }
    }

    void MoveEntityByInput(Entity entity)
    {
        if (!entity.IsValid()) return;
        auto& pb = entity.Get<Physicbody2D>();
        Vector3 position = entity.Get<Transform>().position;

        if (Input::GetKeyPressed(KEY_D))
        {
            pb.RuntimeBody().ApplyForce({ move, 0 }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_A))
        {
            pb.RuntimeBody().ApplyForce({ -move, 0 }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_SPACE))
        {
            pb.RuntimeBody().ApplyForce({ 0, move }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_LEFT_SHIFT))
        {
            pb.RuntimeBody().ApplyForce({ 0, -move }, position.ToBox2D(), true);
        }

        if (Input::GetKeyPressed(KEY_RIGHT))
        {
            pb.RuntimeBody().ApplyTorque(torque, true);
        }
        if (Input::GetKeyPressed(KEY_LEFT))
        {
            pb.RuntimeBody().ApplyTorque(-torque, true);
        }
    }

    void OnFixedUpdate() override
    {
        MoveEntityByInput(entityA);

        time += Time::FixedDeltaTime();

        if (time >= maxTime)
        {
            scene.DestroyEntity(entityD);
            time = 0;
        }

        
    }
};

SHARD_CREATE(Game)
#endif