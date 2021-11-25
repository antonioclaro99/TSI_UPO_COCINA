# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Utensilios(models.Model):
     _name = 'upoCocina.utensilios'
     _description = 'upoCocina utensilios'

     id = fields.int(string="Identificador del utensilio", required=True, help="Identificador del utensilio")
     nombre = fields.Char(string="Nombre del utensilio", size=60, required=True, help="Nombre del utensilio")
     descripcion = fields.Char(string="Descripcion del utensilio", size=60, help="Descripcion del utensilio")
