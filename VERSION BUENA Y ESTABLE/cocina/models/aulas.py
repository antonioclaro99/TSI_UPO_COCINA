# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Aulas(models.Model):
     _name = 'cocina.aulas'
     _description = 'cocina aulas'

     nAula = fields.Integer(string="Numero aula", required=True, help="Numero de nuestro aula")
     capacidadMax = fields.Integer('Capacidad maxima', help="Capacidad maxima de nuestro aula")
     puestos_ids = fields.Many2one("cocina.puestos",string="Lista de puestos")