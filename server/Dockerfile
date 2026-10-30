FROM node:24-bookworm-slim
WORKDIR /app
COPY --chown=node:node package.json ./
COPY --chown=node:node server/account-server.mjs server/static-assets.mjs ./server/
COPY --chown=node:node server/inventory-store.mjs server/inventory-rules.mjs ./server/
COPY --chown=node:node server/post-store.mjs server/request-receipts.mjs server/account-records.mjs server/legacy-records.mjs ./server/
COPY --chown=node:node web/src/application/build-values.mjs web/src/application/equipment-object.mjs web/src/application/item-catalog.mjs web/src/application/catalog-assets.mjs web/src/application/inventory-objects.mjs web/src/application/inventory-merge.mjs web/src/application/boss-target.mjs ./web/src/application/
COPY --chown=node:node web/src/application/registlet-catalog.mjs ./web/src/application/
COPY --chown=node:node web/src/data/skill-tree-data.js web/src/data/my-room-food.js ./web/src/data/
COPY --chown=node:node web/src/data/registlet-levels.mjs ./web/src/data/
COPY --chown=node:node web/src/calculation/stat-registry.js web/src/calculation/calculation-policies.js ./web/src/calculation/
COPY --chown=node:node build/web ./build/web
USER node
EXPOSE 8787
CMD ["node", "--env-file=server/.env", "server/account-server.mjs"]
