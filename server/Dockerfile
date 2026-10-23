FROM node:24-bookworm-slim
WORKDIR /app
COPY --chown=node:node server/account-server.mjs ./server/account-server.mjs
COPY --chown=node:node build/web ./build/web
USER node
EXPOSE 8787
CMD ["node", "--env-file=server/.env", "server/account-server.mjs"]
