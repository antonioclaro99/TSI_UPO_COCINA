# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Aulas(models.Model):
     _name = 'upoCocina.aulas'
     _description = 'upoCocina aulas'

     nAula = fields.Int(string="Numero aula", required=True, help="Numero de nuestro aula")
     capacidadMax = fields.Int('Capacidad maxima', help="Capacidad maxima de nuestro aula")
     puestos_ids = fields.Many2one("upoCocina.puestos",string="Lista de puestos")