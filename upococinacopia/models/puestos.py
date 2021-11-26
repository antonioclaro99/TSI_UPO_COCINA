# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Puestos(models.Model):
     _name = 'upococinacopia.puestos'
     _description = 'upococinacopia puestos'

     nPuesto = fields.Char(string="Nombre puesto", size=60, required=True, help="Nombre de nuestro puesto")
     tipo = fields.Char(string="Tipo de puesto", size=60, required=True, help="Tipo de puesto")
     utensilio_ids = fields.Many2one("upococinacopia.utensilios",string="Lista de utensilios")
     