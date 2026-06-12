# Roadmap

## Milestone 1 - Basic Sync
- Server accepts multiple clients
- Client sends WASD input to server
- Server broadcasts player positions
- Client renders all players as squares

## Milestone 2 - Persistence
- SQLite saves player position on disconnect
- Player spawns at last saved position
- World objects (crates, signs) saved to DB

## Milestone 3 - Basic Polish
- Basic collision
- Player names displayed
- Simple chat

## Milestone 4 - Instancing
- "Enter house" spins up a private zone
- Only owner + invited players can enter
- Objects inside saved per-player