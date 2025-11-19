# Frontend Dockerfile
FROM nginx:alpine

# Copia tutti i file statici nel percorso di default di nginx
COPY . /usr/share/nginx/html

# Comando di default
CMD ["nginx", "-g", "daemon off;"]