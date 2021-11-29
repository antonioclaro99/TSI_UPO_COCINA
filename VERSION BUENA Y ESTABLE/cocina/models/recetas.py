# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Recetas(models.Model):
    _name = 'cocina.recetas'
    _description = 'cocina recetas'

    nombre = fields.Char(string="Nombre Receta", size=60, required=True, help="Nombre de nuestra receta")
    descripcion = fields.Text(string="Descripcion", help="Descripcion de nuestra receta")
    duracion = fields.Integer(string="Duracion", help="Duracion en min")
    lineaingrediente_ids = fields.Many2many("cocina.lineaingrediente", string="Lista de ingredientes")
    precioReceta = fields.Float(string="Precio total", compute='_compute_total')
    cursos_ids = fields.Many2many("cocina.cursos", string="Lista de cursos")

    _sql_constraints = [('recetas_nombre_unique','UNIQUE (nombre)','El nombre debe ser único')]

    
    @api.depends('lineaingrediente_ids', 'lineaingrediente_ids.precioTotal')
    def _compute_total(self):   
        for linea in self:
            precioActual = 0
            if linea.precioReceta != 0:
                precioActual = linea.precioReceta

            for ingrediente in linea.lineaingrediente_ids:
                precioActual += ingrediente.precioTotal
                
            linea.precioReceta = precioActual