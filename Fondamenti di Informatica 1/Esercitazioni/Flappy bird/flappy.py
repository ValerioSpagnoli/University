import pygame
import sys
import random

pygame.init()

schermo = pygame.display.set_mode((288, 512))
pygame.display.set_caption('Flappy Bird')
pygame.display.flip()

FPS = 50
vel_avanz = 3

sfondo = pygame.image.load('sfondo.png')
uccello = pygame.image.load('uccello.png')
base = pygame.image.load('base.png')
gameover = pygame.image.load('gameover.png')
tubo_giu = pygame.image.load('tubo.png')
tubo_su = pygame.transform.flip(tubo_giu, False, True)

class tubi_classe:
    def __init__(self):
        self.x = 300
        self.y = random.randint(-75, 150)
    def avanza_e_disegna(self):
        self.x -= vel_avanz
        schermo.blit(tubo_giu, (self.x, self.y+210))
        schermo.blit(tubo_su, (self.x, self.y-210))
        

def inizializza():
    global uccellox, uccelloy, uccello_vely
    global basex
    global tubi
    uccellox = 60
    uccelloy = 150
    uccello_vely = 0
    basex = 0
    tubi = [ ]
    tubi.append(tubi_classe())

def game_over():
    schermo.blit(gameover, (50,180))
    aggiorna()
    restart = False
    while not restart:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
                inizializza()
                restart = True
            elif event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

def disegna_oggetti():
    schermo.blit(sfondo, (0, 0))
    for t in tubi:
        t.avanza_e_disegna()
    schermo.blit(uccello, (uccellox, uccelloy))
    schermo.blit(base, (basex, 404))

def aggiorna():
    pygame.display.update()
    pygame.time.Clock().tick(FPS)
    

inizializza()

while True:
    basex -= vel_avanz
    if basex < -45:
        basex = 0
    uccello_vely += 1
    uccelloy += uccello_vely
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif (event.type == pygame.KEYDOWN and event.key == pygame.K_UP):
            uccello_vely = -10
    if tubi[-1].x < 150:
        tubi.append(tubi_classe())
    if uccelloy > 381:
        game_over()
    disegna_oggetti()
    aggiorna()
    
