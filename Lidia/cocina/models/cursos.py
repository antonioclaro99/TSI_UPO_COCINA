# -*- coding: utf-8 -*-

from odoo import models, fields, api


class Cursos(models.Model):
     _name = 'cocina.cursos'
     _description = 'cocina cursos'

     nombre = fields.Char(string="Nombre Curso", size=60, required=True, help="Nombre de nuestra curso")
     tipo = fields.Selection([('diseno', 'Cocina de diseño'),('lactosa','Para intolerantes a la lactosa'),('huevo','Para intolerantes al huevo'),('frutossecos','Para intolerantes a los frutos secos'),('marisco','Para intolerantes al marisco'),('gluten','Para celiacos'),('combinado','Para todas las intolerancias')], 'Tipo')
     fechaInicio = fields.Datetime('Fecha inicio', help="Fecha de inicio de nuestro curso")
     fechaFin = fields.Datetime('Fecha fin', help="Fecha de finalizacion de nuestro curso")
     recetas_ids = fields.Many2many("cocina.recetas", string="Lista de recetas")
     precioCurso = fields.Float(string="Precio curso", compute='_compute_total')

     @api.depends('recetas_ids')
     def _compute_total(self):   
        for linea in self:
            precioActual = 0
            if linea.precioCurso != 0:
                precioActual = linea.precioCurso

            for receta in linea.recetas_ids:
                precioActual += receta.precioReceta
                
            linea.precioCurso = precioActual + (precioActual * 0.5) + 10