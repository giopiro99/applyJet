NAME = apply-jet

COMPOSE = docker compose -f docker-compose.yml

all: build up

build:
	$(COMPOSE) build

up: 
	$(COMPOSE) up -d

down:
	$(COMPOSE) down

fclean: down
	docker system prune -a

re: down fclean all