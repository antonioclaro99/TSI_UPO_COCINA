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
    recetas_ids = fields.Many2many("cocina.recetas", string="Lista de recetas donde usamos este ingrediente")