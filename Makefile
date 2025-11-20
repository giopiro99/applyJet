NAME = apply-jet

COMPOSE = docker compose -f docker-compose.yml

all: build up

build:
	@echo "Costruzione dei container in corso.."
	@$(COMPOSE) build --quiet >/dev/null 2>&1

up:
	@echo "Accensione dei container in corso.."
	@echo "Vai su https://localhost:8443 per vedere il calcolatore"
	@$(COMPOSE) up -d >/dev/null 2>&1

down:
	@echo "Shutdown dei container in corso.."
	@$(COMPOSE) down >/dev/null 2>&1

fclean: down
	@echo "Distruzione della/e immagine/i in corso.."
	@docker system prune -af >/dev/null 2>&1

re: down fclean all

.PHONY: all build up down fclean re