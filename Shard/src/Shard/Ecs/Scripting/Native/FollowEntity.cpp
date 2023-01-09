#include "shpch.h"
#include "FollowEntity.h"

using namespace Shard;

void FollowEntity::Update()
{
    if (!target.IsValid()) return;
    
    TRANSFORM_REF(target);

    const Vector3 targetPos = targetTr.position;
    const Vector3 pos = Get<Transform>().position;

    if (Vector3::Distance(targetPos, pos) < reachDistance) return;

    const Vector3 moveDir = (targetPos - pos).Normalized();
    Get<Transform>().position += moveDir * Time::DeltaTime();
}