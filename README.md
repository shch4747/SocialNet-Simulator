# Social Network Simulator

A command-line social network engine built in C++ from scratch, without any standard library containers for core data structures. Implements user management, friendship graphs, post storage, friend recommendations, and social distance computation.

## Data Structures

**AVL Tree** — each user's posts are stored in a self-balancing AVL tree keyed by timestamp, guaranteeing O(log n) insertion and O(k) retrieval of the k most recent posts regardless of total post count.

**Adjacency List (unordered_map)** — the social graph is represented as a hash map of username → User, with each User maintaining a set of friends. This gives O(1) average-case user lookup and O(degree) friend traversal.

**BFS** — degrees of separation between any two users is computed via breadth-first search on the friendship graph, returning the shortest path length in O(V + E) time.

**Mutual friend scoring** — friend suggestions are ranked by mutual friend count, with ties broken alphabetically.

## Features

| Command | Description |
|---|---|
| `ADD USER <name>` | Register a new user (case-insensitive) |
| `ADD FRIEND <u1> <u2>` | Create a bidirectional friendship |
| `ADD POST <user> "content"` | Add a timestamped post to a user's feed |
| `LIST FRIENDS <user>` | Print all friends of a user |
| `SUGGEST FRIENDS <user> <N>` | Recommend top N friends by mutual connections |
| `DEGREES OF SEPARATION <u1> <u2>` | Compute shortest social distance via BFS |
| `OUTPUT POSTS <user> <N>` | Retrieve N most recent posts in reverse chronological order |

## Build & Run

```bash
bash build.sh
./socialnet < input.txt
```

Requires g++ with C++17 support.

## Example

```
ADD USER alice
ADD USER bob
ADD USER carol
ADD FRIEND alice bob
ADD FRIEND bob carol
ADD POST alice "Hello world"
DEGREES OF SEPARATION alice carol
SUGGEST FRIENDS alice 1
OUTPUT POSTS alice 1
```

Output:
```
2
carol
"Hello world"
```

## Implementation Notes

- Usernames are normalized to lowercase on input
- AVL tree rotations (LL, RR, LR, RL) are fully implemented from scratch — no `std::map` or `std::set` used for post storage
- BFS returns -1 if no path exists between two users
- Friend suggestions exclude existing friends and the user themselves
