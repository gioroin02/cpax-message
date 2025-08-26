# Pax Message

Things to add:

1. Make the message queue a binary heap to support priority levels

2. Expand the subscription mechanism to allow unsubscriptions

3. Use a tree to search for all the handlers interested in a specific message type and make the leaves linked lists to notify each handler
