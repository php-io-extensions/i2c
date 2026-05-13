<?php

namespace Zephir\Optimizers\FunctionCall;

use Zephir\Call;
use Zephir\CompilationContext;
use Zephir\CompiledExpression;
use Zephir\Exception\CompilerException;
use Zephir\Optimizers\OptimizerAbstract;

class I2cWriteOptimizer extends OptimizerAbstract
{
    public function optimize(array $expression, Call $call, CompilationContext $context)
    {
        if (!isset($expression['parameters']) || count($expression['parameters']) !== 3) {
            throw new CompilerException("'i2c_write' requires exactly three parameters", $expression);
        }

        $context->headersManager->add('api/i2c-use');

        $resolvedParams = $call->getReadOnlyResolvedParams($expression['parameters'], $context, $expression);

        return new CompiledExpression(
            'long',
            'i2c_write(' . $resolvedParams[0] . ', ' . $resolvedParams[1] . ', ' . $resolvedParams[2] . ')',
            $expression
        );
    }
}
