# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Ingredientes(models.Model):
    _name = 'cocina.ingredientes'
    _description = 'cocina ingredientes'

    nombre = fields.Char(string="Nombre Ingrediente", size=60, required=True, help="Nombre del ingrediente")
    precio = fields.Float(string="Precio", help="Precio del ingrediente")
    alergeno = fields.Selection([('gluten', 'Gluten'),
                                  ('lactosa','Lactosa'),
                                  ('huevo','Huevo'),
                                  ('frutossecos','Frutos Secos'),
                                  ('marisco','Marisco')], 'Alergeno')
    stock = fields.Boolean(string="Stockboo")
    mensajeStock = fields.Char(string="Stock", compute='_compute_stock')

    _sql_constraints = [('ingredientes_nombre_unique','UNIQUE (nombre)','El nombre debe ser único')]
    
    def btn_stockSi(self):
          self.write({'stock':True})

    def btn_stockNo(self):
          self.write({'stock':False})

    @api.depends('stock')
    def _compute_stock(self):
        for linea in self:
            linea.mensajeStock = "No hay stock disponible"
            if linea.stock == True:
                linea.mensajeStock = "Hay stock disponible"
            