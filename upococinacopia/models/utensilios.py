# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Utensilios(models.Model):
     _name = 'upococinacopia.utensilios'
     _description = 'upococinacopia utensilios'

     id = fields.Integer(string="Identificador del utensilio", required=True, help="Identificador del utensilio")
     nombre = fields.Char(string="Nombre del utensilio", size=60, required=True, help="Nombre del utensilio")
     descripcion = fields.Char(string="Descripcion del utensilio", size=60, help="Descripcion del utensilio")
