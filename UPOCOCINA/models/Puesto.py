# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Puesto(models.Model):
     _name = 'upoCocina.puesto'
     _description = 'upoCocina puesto'

     nPuesto = fields.Char(string="Nombre Clase", size=60, required=True, help="Nombre de nuestra clase")
     tipo = fields.Char(string="Tipo de puesto", size=60, required=True, help="Tipo de puesto")
     utensilio_ids = fields.Many2one("upoCocina.Utensilio",string="Lista de utensilios")
     