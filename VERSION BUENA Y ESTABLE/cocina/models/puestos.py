# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Puestos(models.Model):

    _name = 'cocina.puestos'
    _description = 'cocina puestos'

    nPuesto = fields.Char(string="Nombre puesto", size=60, required=True, help="Nombre de nuestro puesto")
    tipo = fields.Char(string="Tipo de puesto", size=60, required=True, help="Tipo de puesto")
    utensilio_ids = fields.Many2one("cocina.utensilios",string="Lista de utensilios")
     