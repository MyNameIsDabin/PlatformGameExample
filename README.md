# PlatformGameExample

Cocos2d-x 에서 사용 가능한 플랫폼 게임 예제.

<pre><code>player = Player::create();
player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
player->setMoveSpeed(6.0f);
player->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
addChild(player);
</code></pre>

<pre><code>player->jump(10.0f);</code></pre>
<pre><code>player->moveToDirection(Direction::LEFT);</code></pre>

플레이어가 충돌체로 감지하게 할 노드를 PlatformerContainer 에 따로 추가한다.
<pre><code>PlatformerContainer::getInstance()->pushSolidNode(node);</code></pre>
