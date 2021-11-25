# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Aula(models.Model):
     _name = 'upoCocina.aula'
     _description = 'upoCocina aula'

     nAula = fields.Int(string="Nombre Clase", required=True, help="Numero de nuestro aula")
     capacidadMax = fields.Int('Capacidad maxima', help="Capacidad maxima de nuestro aula")
     puestos_ids = fields.Many2one("upoCocina.Puesto",string="Lista de puestos")