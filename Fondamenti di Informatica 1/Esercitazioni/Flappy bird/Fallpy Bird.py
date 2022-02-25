import pygame
import random

pygame.init()

schermo = pygame.display.set_mode((288,512))

sfondo = pygame.image.load('sfondo.png')
uccello = pygame.image.load('uccello.png')
base = pygame.image.load('base.png')
gameover = pygame.image.load('gameover.png')
tubo_giu = pygame.image.load('tubo.png')
tubo_su = pygame.transform.flip(tubo_giu, False, True)




