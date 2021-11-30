# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Puestos(models.Model):

    _name = 'cocina.puestos'
    _description = 'cocina puestos'
    _rec_name='nPuesto'

    nPuesto = fields.Char(string="Nombre puesto", size=60, required=True, help="Nombre de nuestro puesto")
    tipo = fields.Char(string="Tipo de puesto", size=60, required=True, help="Tipo de puesto")
    utensilio_ids = fields.Many2one("cocina.utensilios",string="Lista de utensilios")
    
    _sql_constraints = [('puestos_nPuesto_unique','UNIQUE (nPuesto)','El nPuesto debe ser único')]
