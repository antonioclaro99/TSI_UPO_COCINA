# -*- coding: utf-8 -*-

from odoo import models, fields, api
from . import ingredientes


class Lineaingrediente(models.Model):
    _name = 'cocina.lineaingrediente'
    _description = 'cocina lineaIngrediente'

    ingrediente_id = fields.Many2one("cocina.ingredientes", string="Ingrediente")
    cantidad = fields.Float(string="Cantidad", help="Cantidad en kilos")
    precioTotal = fields.Float(string="Precio total", compute='_compute_total')
    

    @api.depends('cantidad', 'ingrediente_id')
    def _compute_total(self):
        for linea in self:
            linea.precioTotal = linea.ingrediente_id.precio * linea.cantidad